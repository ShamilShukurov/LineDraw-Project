#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>
// #include <glut.h>
#include <GL/gl.h>
#include "Vector.h"
#include "LineStrip.h"

//distance between mouse click and vertex(edge) has to be smaller than SMALL in order to select it
// SMALL is size of red cross on selected vertex 
// Selected vertex is moved by SMALL value
#define SMALL 5

// ------------------------GENIUS MUTANT LEVEL: SEVERAL CURVES--------------------------------
// — In create mode :
//      — everything works as in the previous stages ;
//      — Pressing the ENTER key switches the system to object mode ;
// — In object mode :
//      — clicking near a line strip selects that line strip ;
//      — pressing the backspace key removes the selected line strip ;
//      — pressing ’n’ key switches to create mode in order to create a new strip ;
//      — pressing ENTER enters the component mode ;
// — In component mode :
//      — The component mode works as the edit mode in the previous stage.
//      — Pressing the ENTER key switches to object mode.
//      — Pressing the ’n’ key switches to create mode in order to add vertices to the same strip.
// — Pressing the Escape key exits the program.

// — Additional Features:
//     — Current mode is always displayed in screen 
//     — In edit mode pressing 'a' selects next vertex of selected vertex
//     — In edit mode pressing 'd' selects previous vertex of selected vertex

// Notes:
//      - color of selected linestrip is gray (or looks like gray rgb(150,130,110))
//        color of selected edge is purple (rgb(100,255,100))
//        color of linestrips is black in create mode, blue in object mode, green in component
//      - if program is in object mode, if user deletes all linestrips, program
//          automatically switches to create mode;
//      - if program is in component mode and user deletes vertices of selected linestrip,
//          when there is less than two vertices, program switches to create mode;
//          After that if user delete last vertex, program stays in create mode, and user
//          can draw new linestrip. If user want to choose other linestrip to edit or add vertices,
//          he can change mode to Object
// ------------------------------------------------------------------------------------------