#include "LineDraw.h"

// ----------------GLOBAL VARIABLES---------------------
// width and height of window
int window_width, window_height;
// Linestrip that holds vertices; empty at the beginning
LineStrip* linestrip=NULL;
// Mode: 0-create;1-edit.
int mode=0;
// selected vertex
LineStrip* selectedVertex=NULL;
// previous node of selected vertex
LineStrip* previousVertex=NULL;
// Selected Edge is represented by its two vertices
LineStrip* selectedEdge = NULL ;
// -----------------------------------------------------

// -----------------------------------------------------
//     NOTE:
// The reason behind using global variable 
// previousVertex is efficiency: 
// when we want to delete element from list,
//  if we know previous node, it happens in constant
// time, otherwise we have to traverse
// the list until we find the previous node of the element
// -----------------------------------------------------

// --------------------FUNCTION PROTOTYPES-----------------------------


//-------------------------------------------------------------
// Draws a red cross of size size pixels at point (x,y)
static void _drawRedCross(int x, int y, int size);

// -----------------------------------------------------------------------
// r,g,b: int values represent components of color with which vertices will be drawn
// Function draws all vertices in all linestrips
static void _drawVertices(int r, int g, int b);

// -----------------------------------------------------------------------
// x,y : int values represent coordinates of text
// r,g,b: float values represtent color
// font: font in which text will be written
// Function displays name of current mode in the given position of screen
//          with given font and color 
static void modeInfo(int x, int y, float r, float g, float b, void* font);

// -----------------------------------------------------------------------
// mousePosition: Vector, represents position of mouse click
// If mouse position is near to vertex or edge in linestrip, function selects
// that vertex or edge (assigns values to selectedEdge or selectedVertex).
//  If mouse position is near to vertex, function also determines the value previousVertex.
static void selectEdge_Vertex(Vector mousePosition);

// -----------------------------------------------------------------------
// if vertex is selected, function removes that vertex from linestrip
// and after that, assigns new value to selectedVertex 
static void removeSelectedVertex();

// -----------------------------------------------------------------------
// Function changes mode to the Create mode
static void changeToCreate();

// -----------------------------------------------------------------------
// Function changes mode to the Edit mode
static void changeToEdit();


// -------------------------------------------------------------------


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
    if(!LS_isEmpty(linestrip) && selectedVertex!=NULL){
        _drawRedCross((selectedVertex->value).x,(selectedVertex->value).y,SMALL);
    }
    // color of vertices also depends on mode: black in create mode; green in edit mode
    if(mode==0){
        _drawVertices(0,0,0);
    }
    else if(mode==1){
        _drawVertices(0,255,0);
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
        // counter of mouse clicking
    
	if(state==GLUT_DOWN &&button==GLUT_LEFT_BUTTON){
        if(mode==0){
            Vector nvertex = V_new(x,y); // new Vertex
            LS_push(&linestrip, nvertex);
            selectedVertex=linestrip;
        }
        else if(mode==1){
            Vector mousePosition = V_new(x,y);
            selectEdge_Vertex(mousePosition);
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
        if(mode==0){
            LS_pop(&linestrip);
            selectedVertex=linestrip;
        }
        else if(mode==1){
            removeSelectedVertex();
            if(!LS_isSizeGreater(linestrip,1)){
                changeToCreate();
            }
        }
        glutPostRedisplay();
        break;
    case 13:             // Enter
        changeToEdit();
        glutPostRedisplay();
        break;
    case 'n':
        changeToCreate();
        glutPostRedisplay();
        break;
    case 'i' :
        if(mode==1){
            if(selectedEdge!=NULL && selectedEdge->next!=NULL){
                Vector middle = V_middle(selectedEdge->value, selectedEdge->next->value);
                LS_addAfterNode(selectedEdge,middle);
                selectedVertex=selectedEdge->next;
                previousVertex=selectedEdge;
                selectedEdge=NULL;
            }
        }
        glutPostRedisplay();
        break;
    case 'a':
        if(mode==1 && selectedVertex!=NULL){
            if(selectedVertex->next!=NULL){
                previousVertex=selectedVertex;
                selectedVertex=selectedVertex->next;
            }
        }
        glutPostRedisplay();
        break;
    case 'd':
        if(mode==1){
            selectedVertex=linestrip;
            previousVertex=NULL;
        }
        glutPostRedisplay();
        break;
	}
}
//-------------------------------------------------------------
// The call back function which is called each time that
// a special key (arrows, function keys) is pressed.

static void _special_CB(int key, int x, int y)
{   // In edit mode arrow keys move the selected vertex to corresponding direction
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




// Function for drawing Line Strip
static void _drawVertices(int r, int g, int b){    
    LineStrip* temp=linestrip;
    glBegin(GL_LINE_STRIP);
    while (temp!=NULL){
        glColor3ub(r,g,b);
        if(selectedEdge!=NULL && temp==selectedEdge->next){
            glColor3b(100,255,100);
        }
		glVertex2i(temp->value.x,temp->value.y);
        temp=temp->next;
    }
    glEnd();
    
}

//-------------------------------------------------------------
// Draws a red cross of size size pixels at point (x,y)

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



static void selectEdge_Vertex(ltype mousePosition){

    LineStrip* temp= linestrip;
    LineStrip* prev = NULL;
    if(LS_isEmpty(temp)){
        return;
    }
    while(temp->next!=NULL){
        Vector vertex1=temp->value;
        Vector vertex2=temp->next->value;
        // if mousePosition is near to vertex, select that vertex and set selectedEdge null
        if(V_isNear(mousePosition,vertex1,SMALL)){
            selectedEdge=NULL;
            selectedVertex=temp;
            break;
            
        }
        else if(V_isNear(mousePosition,vertex2,SMALL)){
            selectedEdge=NULL;
            prev=temp;
            selectedVertex = temp->next;
            break;
        }
        // if mousePosition is near to edge, select that edge and set selectedVertex null
        else if(V_PtSegmentDistance(mousePosition,vertex1,vertex2)<SMALL){
            selectedVertex=NULL;
            selectedEdge=temp;
            break;
        }
        prev=temp;
        temp=temp->next;
    }

    // if vertex selected change global variable
    if(selectedVertex!=NULL){
        previousVertex=prev;
    }
    
}

// Function for giving info to user about current mode
static void modeInfo(int x, int y, float r, float g, float b, void* font){
    char *string = (char*)calloc(20,sizeof(char));
    if(mode==0){
        string="Create Mode";
    }
    else if(mode==1){
        string="Edit Mode";
    }
    glColor3f( r, g, b );
    glRasterPos2f(x, y);
    for (int i = 0; string[i]!='\0'; i++) {
        glutBitmapCharacter(font, string[i]);
  }
}

static void changeToCreate(){
    if(mode==1){
        mode=0;
        selectedVertex=linestrip;
        selectedEdge=NULL;
    }
}

static void changeToEdit(){
    if(mode==0 && LS_isSizeGreater(linestrip,1)){
        mode=1;
        selectedVertex=NULL;
    }
    else if(mode==0 && !LS_isSizeGreater(linestrip,1)){
        printf("There should be at least 2 vertices in linestrip in order to edit it\n");
    }
}
static void removeSelectedVertex(){
    if(selectedVertex!=NULL){
        if(selectedVertex==linestrip){
            LS_pop(&linestrip);
            selectedVertex=linestrip;
        }
        else{
            LS_removeAfterNode(previousVertex);
            if(previousVertex->next!=NULL){
                selectedVertex=previousVertex->next;
            }
            else{
                selectedVertex=previousVertex;
                previousVertex=LS_previous(linestrip,selectedVertex);
            }
        }
    }
}