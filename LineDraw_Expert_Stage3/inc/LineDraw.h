#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>
// #include <glut.h>
#include <GL/gl.h>
#include "Vector.h"
#include "LineStrip.h"

// -----------------EXPERT LEVEL:Creating and removing vertices ------------------- 
// — When the program is launched, we only have a white window with no vertices and no edges ;
// — Each time the user makes a left mouse click, a new vertex is added at the position of the click ;
// — Each time the user presses the Backspace key, the last vertex is removed ;
// — Pressing the Escape key exits the program.
