#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <sys/stat.h>

using namespace std;

struct point {
    double x, y, z;
    point(){}
    point(double x, double y, double z) : x(x), y(y), z(z) {}
};

void initializeGlut(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

vector< vector< point > > controlPoints;
vector< vector<int> > C;

double cameraDistance = 200, cameraRotationAroundY = -45.0/2, cameraRotationAroundX = 45.0/2;

void readControlPoints(char * file) {
    printf("Will read points from %s\n", file);
    ifstream fin(file);
    controlPoints.clear();
    int n, m;
    fin >> n >> m;
    printf("There are n=%d x m=%d control points\n", n, m);
    for (int i = 0; i < n; ++i) {
        controlPoints.push_back( vector<point>() );
        for (int j = 0; j < m; ++j) {
            double x, y, z;
            fin >> x >> y >> z;
            printf("Read control point <%lf, %lf, %lf>\n", x, y, z);
            controlPoints.back().push_back( point(x, y, z) );
        }
    }
    assert(controlPoints.size() == n);
    assert(controlPoints[0].size() == m);
}

void precomputeBinomialCoefficients() {
    int n = (int)max(controlPoints.size(), controlPoints[0].size());
    printf("Precomputing binomial coefficients up to n x n = %d x %d...\n", n, n);
    
    C.assign(n + 1, vector<int>(n + 1, 0) ); // Binomial coefficients
    C[0][0] = 1;
    for (int i = 1; i <= n; ++i){
        for (int j = 0; j <= n; ++j) {
            C[i][j] = C[i-1][j];
            if (j > 0) C[i][j] += C[i-1][j-1];
        }
    }
}

inline double bernstein(int n, int i, double u) {
    double ans = C[n][i] * pow(u, i) * pow(1.0 - u, n - i);
    return ans;
}

point P(double u, double v) {
    point ans(0, 0, 0);
    int n = (int)controlPoints.size();
    int m = (int)controlPoints[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            double k = bernstein(n - 1, i, u) * bernstein(m - 1, j, v);
            ans.x += k * controlPoints[i][j].x;
            ans.y += k * controlPoints[i][j].y;
            ans.z += k * controlPoints[i][j ].z;
        }
    }
    return ans;
}

void drawBezierCurveWithConstantU(double u) {
    glBegin(GL_LINES);    
    double delta = 0.01;
    for (double v = 0.0; v < 1.0 - delta; v += delta) {
        point p1 = P(u, v);
        point p2 = P(u, v + delta);
        
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
    }
    glEnd();    
}

void drawBezierCurveWithConstantV(double v) {
    glBegin(GL_LINES);    
    double delta = 0.01;
    for (double u = 0.0; u < 1.0 - delta; u += delta) {
        point p1 = P(u, v);
        point p2 = P(u + delta, v);
        
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
    }
    glEnd();    
}



void drawBezierSurface(){    
    for (int i = 0; i < controlPoints.size(); ++i){
        for (int j = 0; j < controlPoints[i].size(); ++j){
            // Draw straight lines between control points
            glBegin(GL_LINES);            
            if (j + 1 < controlPoints[i].size()) { 
                glVertex3i(controlPoints[i][j].x, controlPoints[i][j].y, controlPoints[i][j].z);
                glVertex3i(controlPoints[i][j+1].x, controlPoints[i][j+1].y, controlPoints[i][j+1].z);
            }
            if (i + 1 < controlPoints.size()) {
                glVertex3i(controlPoints[i][j].x, controlPoints[i][j].y, controlPoints[i][j].z);
                glVertex3i(controlPoints[i+1][j].x, controlPoints[i+1][j].y, controlPoints[i+1][j].z);            
            }
            glEnd();

            // Draw control points as little white spheres
            const point &p = controlPoints[i][j];
            glColor3f(1.0, 1.0, 1.0);            
            glPushMatrix();
            glTranslatef(p.x, p.y, p.z);
            glutSolidSphere(1, 10, 10);
            glPopMatrix();
            
            glColor3f(0.5, 0.5, 0.5);
        }
    }
    
    glColor3f(1, 1, 0);
    printf("Drawing Bézier curves with constant u...\n");
    for (double u = 0; u <= 1.0; u += 0.1) {
        drawBezierCurveWithConstantU(u);
    }
    printf("Drawing Bézier curves with constant v...\n");    
    for (double v = 0; v <= 1.0; v += 0.1) {
        drawBezierCurveWithConstantV(v);
    }
    printf("Done!\n");
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(0, 0, cameraDistance,   0, 0, 0,   0, 1, 0);
    glRotatef(cameraRotationAroundX,    1, 0, 0);
    glRotatef(cameraRotationAroundY,    0, 1, 0);
    
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(100, 0, 0);
    
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100, 0);
        
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 100);
    glEnd();
    
    // Draw little points at the pointing end of axes
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(100, 0, 0);
    glRotatef(90, 0, 1, 0);
    glutSolidCone(1, 4, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(0, 100, 0);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(1, 4, 10, 10);
    glPopMatrix();    

    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(0, 0, 100);
    glutSolidCone(1, 4, 10, 10);
    glPopMatrix();    
    
    
    drawBezierSurface();
    
    glutSwapBuffers();
}

void reshape(int newWidth, int newHeight){
    glViewport(0, 0, newWidth, newHeight);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.0, 1000.0);
    //gluPerspective(30.0, 1.0, 1.0, 500.0);
}

void keyboard(unsigned char key, int x, int y){
    if (key == 'w') {
        if (cameraDistance - 10 >= 5) cameraDistance -= 10;
    } else if (key == 's') {
        cameraDistance += 10;
    } else if (key == 'a') {
        cameraRotationAroundY -= 5;
    } else if (key == 'd') {
        cameraRotationAroundY += 5;
    } else if (key == 'q') {
        cameraRotationAroundX -= 5;
    } else if (key == 'e') {
        cameraRotationAroundX += 5;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    
}

int main(int argc, char **argv) {
    if (argc < 2){
        fprintf(stderr, "You need to pass the name of the file with the control points as an argument.\n");
        fprintf(stderr, "   Example: %s %s\n", argv[0], "/tmp/myControlPoints.txt");        
        return -1;
    }

    struct stat st;
    if (stat(argv[1], &st) != 0) {
        fprintf(stderr, "The file '%s' does not exist.\n", argv[1]);
        return -1;
    }
    
    readControlPoints(argv[1]);
    precomputeBinomialCoefficients();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bézier Curves");
    glutDisplayFunc(display);    
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    initializeGlut();
    glutMainLoop();
    return 0;
}
