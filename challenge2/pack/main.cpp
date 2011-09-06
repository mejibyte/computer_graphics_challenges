#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include <cmath>
#include <cassert>
#include <cstdio>
#include <iostream>

const int WINDOW_WIDTH = 600, WINDOW_HEIGHT = 400;
const int XMIN = 100, XMAX = 500, YMIN = 100, YMAX = 300;

const int LEFT = 1 << 0, RIGHT = 1 << 1, BELOW = 1 << 2, ABOVE = 1 << 3;

void init (void) {
    glClearColor (0.0, 0.0, 0.0, 0.0);  // Set display-window color to white.
    // Alpha 0.0 means transparency
    
    glMatrixMode (GL_PROJECTION);       // Set projection parameters.
    // Other values are:
    // GL_MODELVIEW: Transform from world coordinates to camera coordinates
    // GL_PROJECTION: How to project from world to proection surface
    // GL_TEXTURE: How to map from texture to object
    gluOrtho2D (0.0, WINDOW_WIDTH - 1, 0.0, WINDOW_HEIGHT - 1);	// Left, Right, Bottom, Top corners
}

void drawLine(int x0, int y0,     int x1, int y1,    double r = 1, double g = 1, double b = 1) {
	glBegin (GL_LINES);
        glColor3f (r, g, b);
        glVertex2i(x1, y1);
        glVertex2i(x0, y0);    
    glEnd( );
}

int code(int x, int y) {
	int mask = 0;
	if (x < XMIN) mask |= LEFT;
	if (x > XMAX) mask |= RIGHT;
	if (y < YMIN) mask |= BELOW;
	if (y > YMAX) mask |= ABOVE;
	return mask;
}


// Clips and draws the segment of the line that is inside the clipping area.
// Returns: 
//   1 if the line was totally inside
//   2 if the line was totally outside
//   3 if the line was partially inside and partially outside

int clipLine(int x0, int y0,    int x1, int y1) {
	int c0 = code(x0, y0), c1 = code(x1, y1);
	if ((c0 | c1) == 0) { // both inside
		drawLine(x0, y0,    x1, y1,    0, 1, 0);
		return 1;
	}
    
	if ((c0 & c1) != 0) { // both outside
		drawLine(x0, y0,    x1, y1,    1, 0, 0);        
		return 2;
	}
    
	int c = (c0 ? c0 : c1); // pick the code of one outer point
	
	int x, y; // Intersection point
	if (c & BELOW) {
		x = round(x0 + (YMIN - y0) * (x1 - x0) / (y1 - y0));
		y = YMIN;
	} else if (c & ABOVE) {
		x = round(x0 + (YMAX - y0) * (x1 - x0) / (y1 - y0));
		y = YMAX;
	} else if (c & LEFT) {
		x = XMIN;
		y = round(y0 + (y1 - y0) * (XMIN - x0) / (x1 - x0));
	} else if (c & RIGHT) {
		x = XMAX;
		y = round(y0 + (y1 - y0) * (XMAX - x0) / (x1 - x0));
	} else assert(false);
    c == c0 ? drawLine(x, y, x0, y0,  1, 0, 0) : drawLine(x, y, x1, y1,  1, 0, 0); 
	return 2 | (c == c0 ? clipLine(x, y,  x1, y1) : clipLine(x, y, x0, y0));
}

void doEverything (void){
    glClear (GL_COLOR_BUFFER_BIT);  // Clear display window.
	
	// draw clipping area
	drawLine(XMIN, YMIN, XMAX, YMIN);
	drawLine(XMIN, YMAX, XMAX, YMAX);
	drawLine(XMAX, YMIN, XMAX, YMAX);
	drawLine(XMIN, YMIN, XMIN, YMAX);    
            
    srand((unsigned int)time(NULL));
    bool inside = false, outside = false, mixed = false;
    while (!inside || !outside || !mixed){
    
        int x0 = rand() % WINDOW_WIDTH;
        int y0 = rand() % WINDOW_HEIGHT;
        
        int x1 = rand() % WINDOW_WIDTH;
        int y1 = rand() % WINDOW_HEIGHT;
        
        int where = clipLine(x0, y0, x1, y1);
        if (where == 1) inside = true;
        else if (where == 2) outside = true;
        else if (where == 3) mixed = true;
        else assert(false);
	}
    
    glFlush( );     // Process all OpenGL routines as quickly as possible.
}

int main (int argc, char** argv) {
    glutInit (&argc, argv);                         // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   // Set display mode.
    glutInitWindowPosition (50, 100);   // Set top-left display-window position.
    glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT);      // Set display-window width and height.
    glutCreateWindow ("Cohen-Sutherland Line Clipping Algorithm"); // Create display window.
    
    init ( );                            // Execute initialization procedure.
    glutDisplayFunc (doEverything);       // Send graphics to display window.
    glutMainLoop ( );                    // Display everything and wait.
    return 0;
}