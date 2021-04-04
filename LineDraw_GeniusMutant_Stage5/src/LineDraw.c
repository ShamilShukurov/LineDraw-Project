#include"LineDraw.h"
// ----------------GLOBAL VARIABLES---------------------
// width and height of window
int window_width, window_height;
// Linestrip List that holds all linestrips
LineStrip* linestripList=NULL;

LineStrip* selectedLinestrip=NULL;
// Mode: 0-create;1-edit; 2-component.
// program is in create mode in the beginning
int mode=0;

LineStrip* selectedVertex=NULL;

LineStrip* selectedEdge ;
// -----------------------------------------------------


//                *FUNCTION PROTOTYPES*

//-----------------------------------------------------------------------
// Draws a red cross of size size pixels at point (x,y)
static void _drawRedCross(int x, int y, int size);

// -----------------------------------------------------------------------
// x,y : int values represent coordinates of text
// r,g,b: float values represtent color
// font: font in which text will be written
// Function displays name of current mode in the given position of screen
//          with given font and color 
static void modeInfo(int x, int y, float r, float g, float b, void* font);

// -----------------------------------------------------------------------
// Function changes mode to the Create mode
static void changeToCreate();

// -----------------------------------------------------------------------
// Function changes mode to the Component mode
static void changeToComponent();

// -----------------------------------------------------------------------
// Function changes mode to the Object mode
static void changeToObject();

// -----------------------------------------------------------------------
// r,g,b: int values represent components of color with which vertices will be drawn
// Function draws all vertices in all linestrips
static void _drawVertices(int r, int g, int b);

// -----------------------------------------------------------------------
// linestrip: pointer to head node of one linestrip
// mousePosition: Vector, represents position of mouse click
// if mouse position is near to vertex or edge in linestrip, function selects
// that vertex or edge (by global variable).
// precondition: if linestrip is null or not head node (linestrip->isHead=NULL)
// function terminates without doing anything
static LineStrip* selectEdge_Vertex(LineStrip* linestrip, Vector mousePosition);

// -----------------------------------------------------------------------
// mousePosition: Vector, represents position of mouse click
// if mouse position is near to any linestrip in whole list of linestrips
// function selects that linestrip
static void selectLineStrip(Vector mousePosition);


//                  *CALLBACK FUNCTIONS*

//-------------------------------------------------------------
// The call back function which is called each time that we need
// to draw everything again. All your drawings should be called
// in this function. Initially, we only draw a cross.

static void _display_CB()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glOrtho(0,window_width,window_height,0,-1,1);
    glShadeModel(GL_FLAT);
    glClear(GL_COLOR_BUFFER_BIT);

	// Let the current color be black
	glColor3ub(0,0,0);
        modeInfo(10,10,0,0,0,GLUT_BITMAP_8_BY_13);

    // show selected vertex by red cross
    if(!LS_isEmpty(linestripList) && selectedVertex!=NULL){
        _drawRedCross((selectedVertex->value).x,(selectedVertex->value).y,SMALL);
    }
    // color of vertices also depends on mode: black in create mode; green in edit mode
    if(mode==0){
        _drawVertices(0,0,0);
    }
    else if(mode==1){
        _drawVertices(0,255,0);
    }
    else if(mode==2){
        _drawVertices(0,0,255);
    }

	glFlush();
    glutSwapBuffers();

}

//-------------------------------------------------------------
// The call back function which is called each time that the
// graphical window is resized.

static void _reshape_CB(int width, int height)
{
	window_width = width;
	window_height = height;
    glViewport(0, 0,window_width,window_height);
}

//-------------------------------------------------------------
// The call back function which is called each time that
// a mouse button is pressed or released.

static void _mouse_CB(int button, int state, int x, int y){
        
    
	if(state==GLUT_DOWN &&button==GLUT_LEFT_BUTTON){
        Vector mousePosition = V_new(x,y);
        if(mode==0){
            LS_push(&linestripList,&selectedLinestrip,mousePosition);
            selectedVertex=selectedLinestrip;
        }
        else if(mode==1){
            selectEdge_Vertex(selectedLinestrip,mousePosition);
        }
        else if(mode==2){
            selectLineStrip(mousePosition);
            glutPostRedisplay();
        }

    }
	
	glutPostRedisplay();
}


//-------------------------------------------------------------
// The call back function which is called each time that
// a key (corresponding to an ascii code) on the keyboard is pressed.

static void _keyboard_CB(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27 :  exit(0); break; // escape key
	case 8 :                   // backspace key
        if(mode==0 || mode==1){
            if(selectedVertex!=NULL){
                LineStrip* temp=NULL;
                if(selectedVertex->next!=NULL && selectedVertex->next->isHead==false){
                    temp=selectedVertex->next;
                }
                else if(selectedVertex->previous!=NULL && selectedVertex!=selectedLinestrip){
                    temp=selectedVertex->previous;
                }
                LS_removeNode(&linestripList,&selectedLinestrip,selectedVertex);
                selectedVertex=temp;
            }
            if(!LS_isSizeGreater(selectedLinestrip,1)){
                 changeToCreate();
            }
        }
        else if(mode==2){
            if(!LS_isEmpty(selectedLinestrip)){
                LSL_removeStrip(&linestripList,&selectedLinestrip);
                if(LS_isEmpty(selectedLinestrip)){
                    selectedLinestrip=linestripList;
                }
            }
            if(LS_isEmpty(linestripList)){
                changeToCreate();
            }
        }
        glutPostRedisplay();
        break;
    
    case 13:             // Enter
        if(mode==0 || mode==1){
            changeToObject();
        }
        else if(mode==2){
            changeToComponent();
        }
        glutPostRedisplay();
        break;
    case 'n':
        changeToCreate();
        glutPostRedisplay();
        break;

    
    case 's':
        printf("elements:\n");
        LSL_print(linestripList);
        break;
    case 'i' :
        if(mode==1){
            if(selectedEdge!=NULL && selectedEdge->next!=NULL){
                Vector middle = V_middle(selectedEdge->value, selectedEdge->next->value);
                LS_insertAfter(selectedEdge,middle,false);
                selectedVertex=selectedEdge->next;
                selectedEdge=NULL;
            }
        }
        glutPostRedisplay();
        break;
    case 'a':
        if(mode==1 && selectedVertex!=NULL){
            if(selectedVertex->next!=NULL && selectedVertex->next->isHead==false){
                selectedVertex=selectedVertex->next;
            }
        }
        glutPostRedisplay();
        break;
    case 'd':
        if(mode==1 && selectedVertex!=NULL){
            if(selectedVertex->isHead==false && selectedVertex->previous!=NULL){
                selectedVertex=selectedVertex->previous;
            }
        }
        glutPostRedisplay();
        break;
	}
}
//-------------------------------------------------------------
// The call back function which is called each time that
// a special key (arrows, function keys) is pressed.

static void _special_CB(int key, int x, int y)
{   // In component mode arrow keys move the selected vertex to corresponding direction
    if(mode==1){
        switch(key)
        {
        case GLUT_KEY_LEFT : 
        // if selected vertex is not null and doesn't pass window width
            if(selectedVertex!=NULL && selectedVertex->value.x>SMALL){
                V_move(&(selectedVertex->value),-SMALL,0);
                glutPostRedisplay();
            }
            break;
        case GLUT_KEY_RIGHT:
        
            if(selectedVertex!=NULL && selectedVertex->value.x<window_width-SMALL ){
                V_move(&(selectedVertex->value),SMALL,0);
                glutPostRedisplay();
            }
            break;
        case GLUT_KEY_UP   :
            if(selectedVertex!=NULL && selectedVertex->value.y>SMALL){ // 
                V_move(&(selectedVertex->value),0,-SMALL);
                glutPostRedisplay();
            }
            break;
        case GLUT_KEY_DOWN :
            if(selectedVertex!=NULL && selectedVertex->value.y<window_height-SMALL){ // 
                V_move(&(selectedVertex->value),0,SMALL);
                glutPostRedisplay();
            }
            break;
        default : fprintf(stderr,"Unknown special key.\n");
        }
        
    }
}

int main(int argc, char **argv)
{
	if(argc!=3)
	{
		printf("\nUsage : %s <width> <height>\n\n",argv[0]);
		return 1;
	}
	else
	{
		// Reading the command line arguments
		window_width = atoi(argv[1]);
		window_height = atoi(argv[2]);

		int windowPosX = 100, windowPosY = 100;

		// Initializing GLUT (graphic window and events manager)
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
		glutInitWindowSize(window_width,window_height);
		glutInitWindowPosition(windowPosX,windowPosY);
		glutCreateWindow(argv[0]);

		// Initializing OpenGL (drawing tool)
		glViewport(0, 0, window_width, window_height);
		glClearColor(255,255,255,0);

		// Associating callback functions to each type of event
		glutDisplayFunc(_display_CB);
		glutReshapeFunc(_reshape_CB);
		glutKeyboardFunc(_keyboard_CB);
		glutMouseFunc(_mouse_CB);
        glutSpecialFunc(_special_CB);
		// Starting the loop which waits for events.
		glutMainLoop();
	}
}


static void modeInfo(int x, int y, float r, float g, float b, void* font) {
    char *string = (char*)calloc(20,sizeof(char));
    if(mode==0){
        string="Create Mode";
    }
    else if(mode==1){
        string="Component Mode";
    }
    else if(mode==2){
        string="Object Mode";
    }
    glColor3f( r, g, b );
    glRasterPos2f(x, y);
    for (int i = 0; string[i]!='\0'; i++) {
        glutBitmapCharacter(font, string[i]);
  }
}

static void _drawRedCross(int x, int y, int size)
{
    
	// Let the current color be red
	glColor3ub(255,0,0);

	// Horizontal line
	glBegin(GL_LINE_STRIP);
	glVertex2i( x-size, y);
	glVertex2i( x+size, y);
	glEnd();

	// Vertical line
	glBegin(GL_LINE_STRIP);
	glVertex2i( x, y-size);
	glVertex2i( x, y+size);
	glEnd();
    
}

static void _drawVertices(int r, int g, int b){
    // color components (stripred,stripgreen,stripblue)
    int sr,sg,sb;
    LineStrip* temp = linestripList;
    while(temp!=NULL){
        
        // color of selected linestrip is different in different modes.
        if(temp==selectedLinestrip && (mode==1 || mode==2)){
            sr=150;sg=130;sb=110;
        }
        else{
            sr=r;sg=g;sb=b;
        }
        // do while loop instead of while, because: 
        // In the first iteration temp->isHead is true but we want to draw it.
        // And also we are sure that for the first iteration temp is not NULL
        glBegin(GL_LINE_STRIP);
        do{
            glColor3ub(sr,sg,sb);
            if(temp->previous==selectedEdge){
                glColor3b(100,255,100);
            }
            glVertex2i(temp->value.x,temp->value.y);
            temp=temp->next;            
        }while(temp!=NULL && !(temp->isHead));
        glEnd();
    }
}

static void changeToCreate(){
    if(mode==1 && selectedLinestrip!=NULL){
        mode=0;
        selectedVertex=selectedLinestrip;
        selectedEdge=NULL;
    }
    else if(mode==1 && selectedLinestrip==NULL){
        printf("You have to select linestrip first in order to add vertices to it\n");
    }
    else if(mode==2){
        mode=0;
        selectedLinestrip=NULL;
        selectedVertex=NULL;
        selectedEdge=NULL;       
    }
}

static void changeToComponent(){
    if(mode==2 && LS_isSizeGreater(selectedLinestrip,1)){
        mode=1;
    }
    else{
        printf("There should be at least 2 vertices in linestrip in order to edit it\n");
    }
}

static void changeToObject(){
    if(mode==0 && LS_isSizeGreater(linestripList,1)){
        mode=2;
        selectedVertex=NULL;
        selectedLinestrip=NULL;
    }
    else if(mode==1){
        mode=2;
        selectedVertex=NULL;
        selectedEdge=NULL;
        selectedLinestrip=NULL;
    }
}

static LineStrip* selectEdge_Vertex(LineStrip* linestrip, Vector mousePosition){
    if(linestrip==NULL || !(linestrip->isHead)){
        return linestrip;
    }
    selectedEdge=NULL;
    selectedVertex=NULL;
    LineStrip* temp=linestrip;  
    while(temp->next!=NULL && temp->next->isHead==false){
        Vector vertex1 = temp->value;
        Vector vertex2 = temp->next->value;
        if(V_isNear(mousePosition,vertex1,SMALL)){
            selectedEdge=NULL;
            selectedVertex=temp;
            break;
        }
        else if(V_isNear(mousePosition,vertex2,SMALL)){
            selectedEdge=NULL;
            selectedVertex=temp->next;
            break; 
        }
        else if(V_PtSegmentDistance(mousePosition,vertex1,vertex2)<SMALL){
            selectedVertex=NULL;
            selectedEdge=temp;
        }
        temp=temp->next;
    }
    return temp->next;
}
static void selectLineStrip(Vector mousePosition){
    selectedLinestrip=NULL;
    LineStrip* temp = linestripList;
    LineStrip* nextHead=NULL;
    while(temp!=NULL){
        nextHead=selectEdge_Vertex(temp,mousePosition);
        if(selectedVertex!=NULL || selectedEdge!=NULL){
            selectedLinestrip=temp;
            selectedVertex=NULL;
            selectedEdge=NULL;
            return;
        }
        temp=nextHead;
    }
}
