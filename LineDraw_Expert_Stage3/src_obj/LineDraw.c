#include"LineDraw.h"

// ----------------GLOBAL VARIABLES---------------------
// width and height of window
int window_width, window_height;
// Linestrip that holds vertices; empty at the beginning
LineStrip* vertices=NULL;
// -----------------------------------------------------


//-------------------------------------------------------------
// r,g,b : int, color components
// Draws all vertices in the linestrip with given color

static void _drawVertices(int r, int g, int b){
	glColor3ub(r,g,b);
    LineStrip* temp=vertices;
	glBegin(GL_LINE_STRIP);
    while (temp!=NULL){
        glVertex2i(temp->value.x,temp->value.y);
        temp=temp->next;
    }
	glEnd();
    
    
}

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
    glClear(GL_COLOR_BUFFER_BIT);

    _drawVertices(0,0,0);

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
		Vector nvertex = V_new(x,y); // new Vertex
        LS_push(&vertices, nvertex);
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
        LS_pop(&vertices);
        glutPostRedisplay();
        break;
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

		// Starting the loop which waits for events.
		glutMainLoop();
	}
}