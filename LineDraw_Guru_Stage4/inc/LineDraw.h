#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>
// #include <glut.h>
#include <GL/gl.h>
#include "Vector.h"
#include "LineStrip.h"

//Distance between mouse click and vertex(edge) has to be smaller than SMALL in order to select it
// SMALL is size of red cross on selected vertex 
// Selected vertex is moved by SMALL value
#define SMALL 5

// ------------------GURU LEVEL:EDITING THE CURVES ---------------------                      
// — In create mode :
//      — everything works as in the previous stage ;
//      — the selected vertex is always the most recent one.
//      — Pressing the ENTER key switches to edit mode ;
// — In edit mode :
//      — clicking near a vertex selects that vertex and unselects everything else ;
//      — clicking near an edge selects that edge and unselects everything else ;
//      — when a vertex is selected, the arrow keys move the selected vertex in the corresponding direction ;
//      — when a vertex is selected, the backspace key removes the selected vertex. 
//          The new selected vertex is next neighbour of the removed vertex.
// — Pressing the Escape key exits the program.

// — Additional Features:
//     — Current mode is always displayed in screen 
//     — In edit mode pressing 'a' selects next vertex of selected vertex
//     — In edit mode pressing 'd' selects head vertex (last added vertex)


// When we select vertex, if two vertices is near to each other and mouse position, 
// the algorithm selects first one in the list. For selecting the second one user can use 'a'  