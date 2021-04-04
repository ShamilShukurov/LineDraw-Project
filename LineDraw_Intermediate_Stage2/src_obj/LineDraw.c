#include "LineDraw.h"

int window_width, window_height;

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

	// Let the current color be black
	glColor3ub(0,0,0);
	
	// Drawing line segment
	glBegin(GL_LINE_STRIP);
	glVertex2i( 100, 100);
	glVertex2i( 300, 100);
	glEnd();

	_drawRedCross(window_width/2,window_height/2,10);

	glFlush();
    glutSwapBuffers();

}

//-------------------------------------------------------------
// The call back function which is called each time that the
// graphical window is resized.

static void _reshape_CB(int largeur, int hauteur)
{
	// printf("Window resized.\n"); // You can comment this line
	window_width = largeur;
	window_height = hauteur;
    glViewport(0, 0,window_width,window_height);
}

//-------------------------------------------------------------
// The call back function which is called each time that
// a mouse button is pressed or released.

static void _mouse_CB(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN && button==GLUT_LEFT_BUTTON){
		Vector clickPos= V_new(x,y);
		Vector A = V_new(100,100); // Point A in AB line segment;
		Vector B = V_new(300,100); // Point B in AB line segment;
		// Point where red cross placed
		Vector center = V_new(window_width/2, window_height/2); 
		printf("---------------------------------------------------------\n");
		printf("Distance between red cross and mouse click:%f\n",V_PtPtDistance(clickPos,center));
		printf("Distance between mouse click and line segment:%f\n",V_PtSegmentDistance(clickPos,A,B));
		printf("---------------------------------------------------------\n");
		glutPostRedisplay();
	}
	
}


//-------------------------------------------------------------
// The call back function which is called each time that
// a key (corresponding to an ascii code) on the keyboard is pressed.

static void _keyboard_CB(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27 :  exit(0); break; // escape key
	}
}



//-------------------------------------------------------------

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









