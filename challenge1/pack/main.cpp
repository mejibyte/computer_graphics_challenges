// Example from Hearn & Baker Computer Graphics with OpenGL.  2004
#include <GLUT/glut.h>      // (or others, depending on the system in use)
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <sys/time.h>

#include <iostream>
#include <utility>
#include <cmath>
#include <cassert>

using namespace std;

typedef pair<int, int> point;

const int SIZE = 500, R = SIZE / 2;

const int NAIVE = 0, BRESENHAM = 1;

int round(float x){ // Rounds to closest integer - only works for nonnegative doubles.
    return floor(x + 0.5);
}

long currentMilliseconds(){
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void drawPoint(const point &somePoint) {
	glBegin(GL_POINTS) ;
    glVertex2i(somePoint.first, somePoint.second);
	glEnd();    
}

void drawSingleLineUsingNaiveAlgorithm(const point &start, const point &end) {
    if (start == end){ drawPoint(start); return; }
    int dx = end.first - start.first, dy = end.second - start.second;
    int size = max(abs(dx), abs(dy));
    for (int t = 0; t < size; ++t) {
        double k = 1.0 * t / size;
        point p = make_pair(round(start.first + k * dx), round(start.second + k * dy));
        drawPoint(p);
    }
}

void drawSingleLineUsingOpenGL(const point &start, const point &end) {
    glBegin (GL_LINES);
    glVertex2i (start.first, start.second);       // Specify line-segment geometry.
    glVertex2i (end.first, end.second);
    glEnd();
}

int getOctant(point start, point end) {
    if (start.first > end.first) swap(start, end); // Make sure dx is always positive
    
    int dx = end.first - start.first;
    int dy = end.second - start.second;
    assert(dx >= 0);
    
    int octant = -1;
    if (dx == 0) { // infinite slope
        octant = 2;
    } else if (0 <= dy && dy < dx) {
        octant = 0;
    }else if (dx <= dy) {
        octant = 1;
    } else if (dy <= -dx) {
        octant = 2;
    } else if (-dx < dy && dy < dx) {
        octant = 3;
    }
    assert(octant != -1);
    return octant;
}

point transformPointForOctant(const point &p, int octant) {
    if (octant == 0) return p;
    if (octant == 1) return make_pair(p.second, p.first);
    if (octant == 2) return make_pair(-p.second, p.first);
    if (octant == 3) return make_pair(-p.first, p.second);
    assert(false);
}

point inverseTransformPointForOctant(const point &p, int octant) {
    if (octant == 0) return p;
    if (octant == 1) return make_pair(p.second, p.first);
    if (octant == 2) return make_pair(p.second, -p.first);
    if (octant == 3) return make_pair(-p.first, p.second);
    assert(false);
}

void drawSingleLineUsingBresenhamsAlgorithm(point start, point end) {
    int octant = getOctant(start, end);

    start = transformPointForOctant(start, octant);
    end = transformPointForOctant(end, octant);        
    
    if (start.first > end.first) swap(start, end); // Make sure dx is always positive
    
    int dx = end.first - start.first;
    int dy = abs(end.second - start.second);
    assert(dx >= 0);

    int p = 2*dy - dx;
    int x = start.first, y = start.second;
    drawPoint(make_pair(x, y));
    while (x < end.first) {
        x++;
        if (p < 0) {
            p += 2 * dy;  
        } else {
            y++;
            p += 2 * (dy - dx);
        }
        drawPoint(inverseTransformPointForOctant(make_pair(x, y), octant));
    }

}

int drawLinesUsingAlgorithm(int algorithm = NAIVE) {
    algorithm == NAIVE ? glClearColor (1.0, 1.0, 1.0, 0.0) : glClearColor (0.0, 0.0, 0.0, 0.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0, SIZE, 0, SIZE);	// Left, Right, Bottom, Top corners

    glClear (GL_COLOR_BUFFER_BIT);  // Clear display window.
    
    int step = 5;
    int count = 0;
    
    while (count < 10000){
        // top to left
        glColor3f(0.0, 0.0, 1.0); //Blue
        for (int i = 0; i <= SIZE; i += step){
            if (algorithm == NAIVE){
                drawSingleLineUsingNaiveAlgorithm(make_pair(0, i), make_pair(i, SIZE));            
            }else{
                drawSingleLineUsingBresenhamsAlgorithm(make_pair(0, i), make_pair(i, SIZE));
            }
            count++;
        }    
        // top to right
        glColor3f(1.0, 0.0, 0.0); //Red
        for (int i = 0; i <= SIZE; i += step){
            if (algorithm == NAIVE){
                drawSingleLineUsingNaiveAlgorithm(make_pair(i, SIZE), make_pair(SIZE, SIZE - i));
            }else{        
                drawSingleLineUsingBresenhamsAlgorithm(make_pair(i, SIZE), make_pair(SIZE, SIZE - i));
            }
            count++;            
        }
        
        // bottom to right
        glColor3f(0.0, 1.0, 0.0); //Green    
        for (int i = 0; i <= SIZE; i += step){
            if (algorithm == NAIVE){
                drawSingleLineUsingNaiveAlgorithm(make_pair(i, 0), make_pair(SIZE, i));
            }else{
                drawSingleLineUsingBresenhamsAlgorithm(make_pair(i, 0), make_pair(SIZE, i));
            }
            count++;            
        }
        
        // bottom to left
        glColor3f(1.0, 1.0, 0.0);//Yellow
        for (int i = 0; i <= SIZE; i += step){
            if (algorithm == NAIVE){
                drawSingleLineUsingNaiveAlgorithm(make_pair(i, 0), make_pair(0, SIZE - i));
            }else{
                drawSingleLineUsingBresenhamsAlgorithm(make_pair(i, 0), make_pair(0, SIZE - i));
            }
            count++;            
        }
    }    
    glFlush();
    return count;
}

void drawLinesUsingNaiveAlgorithm (){
    long millisecondsBeforeStart = currentMilliseconds();
    int count = drawLinesUsingAlgorithm(NAIVE);
    long time = currentMilliseconds() - millisecondsBeforeStart;
    printf("Using naive algorithm:\n");
    printf("Rendered %d lines.\n", count);
    printf("It took %ld milliseconds.\n", time);
    printf("Wow, that sucked!\n");
}

void drawLinesUsingBresenhamsAlgorithm (void){
    long millisecondsBeforeStart = currentMilliseconds();
    int count = drawLinesUsingAlgorithm(BRESENHAM);
    long time = currentMilliseconds() - millisecondsBeforeStart;
    printf("Using Bresenham's algorithm:\n");
    printf("Rendered %d lines.\n", count);
    printf("It took %ld milliseconds.\n", time);
    printf("Whoa, that was fast! Way to go.\n");

}


void testGetOctantIsWorking() {
    // 0
    assert(getOctant(make_pair(0, 0), make_pair(5, 1)) == 0);
    assert(getOctant(make_pair(5, 1), make_pair(6, 1)) == 0);
    assert(getOctant(make_pair(6, 1), make_pair(8, 2)) == 0);
    assert(getOctant(make_pair(0, 0), make_pair(2, 1)) == 0);
    assert(getOctant(make_pair(0, 0), make_pair(-2, -1)) == 0);
    assert(getOctant(make_pair(0, 0), make_pair(-2, -1)) == 0);    
    // 1
    assert(getOctant(make_pair(0, 0), make_pair(1, 1)) == 1);
    assert(getOctant(make_pair(1, 1), make_pair(3, 5)) == 1);
    assert(getOctant(make_pair(1, 1), make_pair(3, 5)) == 1);
    assert(getOctant(make_pair(0, 0), make_pair(1, 1000000000)) == 1);
    assert(getOctant(make_pair(-1, -2), make_pair(-2, -4)) == 1);
    // 2
    assert(getOctant(make_pair(0, 0), make_pair(0, 1)) == 2);
    assert(getOctant(make_pair(3, 5), make_pair(3, 8)) == 2);    
    assert(getOctant(make_pair(0, 0), make_pair(-1, 4)) == 2);
    assert(getOctant(make_pair(0, 0), make_pair(-1, 1)) == 2);   
    // 3
    assert(getOctant(make_pair(0, 0), make_pair(-4, 2)) == 3); 
    assert(getOctant(make_pair(-5, 1), make_pair(-8, 2))== 3);     
    assert(getOctant(make_pair(-5, 1), make_pair(-2000000000, 2))== 3);     
}


int main (int argc, char** argv) {
    testGetOctantIsWorking();
    
    
    glutInit (&argc, argv);                         // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   // Set display mode.
    
    glutInitWindowPosition (50, 100);   // Set top-left display-window position.
    glutInitWindowSize (500, 500);      // Set display-window width and height.
    glutCreateWindow ("Naive algorithm"); // Create display window.
    glutDisplayFunc (drawLinesUsingNaiveAlgorithm);       // Send graphics to display window.
    
    glutInitWindowPosition (650, 100);   // Set top-left display-window position.
    glutInitWindowSize (500, 500);      // Set display-window width and height.
    glutCreateWindow ("Bresenham's algorithm"); // Create display window.
    glutDisplayFunc (drawLinesUsingBresenhamsAlgorithm);       // Send graphics to display window.
    
    glutMainLoop();                    // Display everything and wait.
    return 0;
}

