#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

/*
 *  pyramidWithMaterial
 *  This program demonstrates how to create a sphere and a plane,
 *  with color and lights.
 */
#include <stdlib.h>
#include <math.h>

GLfloat distance = 5.0;
GLfloat increment = 0.1;
GLfloat angle = 0.0;
GLfloat angleIncrement = 0.1;

// Light properties
GLfloat ambient[] = { 0.0, 0.0, 0.0, 0.0 };	
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat position[] = { 5.0, 5.0, 5.0, 0.0 };		// x, y, z, 1:directional 0:point

void init(void) 
{
    //glClearColor (0.0, 0.0, 0.0, 0.0);
    glClearColor(0.0, 0.1, 0.1, 0.0);
    glEnable(GL_DEPTH_TEST);
    //glShadeModel (GL_FLAT);
    glShadeModel(GL_SMOOTH);
    
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    //glLightfv(GL_LIGHT0, GL_POSITION, position);		// position specified here: light moves with camera
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_blue[] = { 0.1, 0.2, 0.8, 1.0 };
    GLfloat mat_red[] = { 0.8, 0.2, 0.1, 1.0 };
    GLfloat mat_green[] = { 0.1, 0.8, 0.1, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat no_shininess[] = { 0.0 };
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    
    
    glLoadIdentity ();             /* clear the matrix */
    /* viewing transformation  */
    //gluLookAt (0.0, 0.0, distance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    GLfloat x = distance * cos(angle);
    GLfloat y = distance * sin(angle);
    /* parameters: where is the camera, looking at vector, up vector */
    gluLookAt (x, y, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glPushMatrix();
    //glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
    //glutWireCube (1.0);
    //glutWireDodecahedron();
    // Materials for the SPHERE
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat); 
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
    //glutSolidCube(1.0);
    // Parameters: Radious, Slices, Stacks
    glutSolidSphere(0.7, 64, 64);
    
    //glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat); 
    // Material for the PLANE
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_green);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
    
    /* A green rectangle */
    glBegin (GL_QUADS);
    glNormal3f (0.0, 0.0, 1.0);
    glVertex3f (0.0, 0.0, 0.0);
    glVertex3f (2.0, 0.0, 0.0);
    glVertex3f (2.0, 2.0, 0.0);
    glVertex3f (0.0, 2.0, 0.0);
    glEnd ( );
    
    /* A red pyramid */
    // Materials for the Pyramid
    //glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat); 
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_red);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
    
    glBegin (GL_TRIANGLES);
    glNormal3f (0.0, -0.5, 0.5);
    glVertex3f (0.0, 0.0, 0.0);
    glVertex3f (1.0, 0.0, 0.0);
    glVertex3f (0.5, 0.5, 1.0);
    glEnd();
    glBegin (GL_TRIANGLES);
    glNormal3f (0.5, 0.0, 0.5);
    glVertex3f (1.0, 0.0, 0.0);
    glVertex3f (1.0, 1.0, 0.0);
    glVertex3f (0.5, 0.5, 1.0);
    glEnd();
    glBegin (GL_TRIANGLES);
    glNormal3f (0.0, 0.5, 0.5);
    glVertex3f (1.0, 1.0, 0.0);
    glVertex3f (0.0, 1.0, 0.0);
    glVertex3f (0.5, 0.5, 1.0);
    glEnd ( );
    glBegin (GL_TRIANGLES);
    glNormal3f (-0.5, 0.0, 0.5);
    glVertex3f (0.0, 1.0, 0.0);
    glVertex3f (0.0, 0.0, 0.0);
    glVertex3f (0.5, 0.5, 1.0);
    glEnd ( );
    
    glPopMatrix();
    
    glLightfv(GL_LIGHT0, GL_POSITION, position);			// position specified here: light position constant in W.C.
    
    glFlush ();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    // parameters for glFrustrum: left, rigth, bottom, top, near, far
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
        case 'w':		
            //Camera.MoveForwards( -0.1 ) ;
            distance -= increment;
            display();
            break;
        case 's':		
            //Camera.MoveForwards( 0.1 ) ;
            distance += increment;
            display();
            break;
        case 'a':		
            //Camera.turnLeft ;
            angle -= angleIncrement;
            display();
            break;
        case 'd':		
            //Camera.turnRight ;
            angle += angleIncrement;
            display();
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}


//#include <vector>
//#include <string>
//#include <algorithm>
//#include <cmath>
//
//using namespace std;
//
//GLfloat cameraDistance = 12, cameraAngle = 0;
//
//// angles = { Y rotation at shoulder, Z rotation at shoulder, Z rotation at elbow, X rotation at wrist }
//int arm_angles[5] = {0, 0, 0, 0, 0};
//enum { SHOULDER_Y, SHOULDER_Z, ELBOW_Z, WRIST_X, WRIST_Z };
//
//void change_angle(int angle, int delta, int minimum = 0, int maximum = 180) {
//    arm_angles[angle] = (arm_angles[angle] + delta) % 360;
//    arm_angles[angle] = max(arm_angles[angle], minimum);
//    arm_angles[angle] = min(arm_angles[angle], maximum);
//}
//
//// Desplegar la escena 3D
//void display(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//    
//    glLoadIdentity();
//    GLfloat x = cameraDistance * sin(cameraAngle);
//    GLfloat z = cameraDistance * cos(cameraAngle);
//    gluLookAt (x, 0.0, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);    
//    
//    
//    glPushMatrix();
//        glRotatef((GLfloat) arm_angles[SHOULDER_Y], 0., 1., 0.);
//        glRotatef((GLfloat) arm_angles[SHOULDER_Z], 0., 0., 1.);
//    
//        glTranslatef(1., 0., 0.);
//        glPushMatrix();
//            glScalef(2.0, 0.4, 1.0);
//            glColor3f(1.0f, 1.0f, 1.0f);
//            glutWireCube(1.);       // shoulder
//        glPopMatrix();
//
//        glTranslatef(1., 0., 0.);
//        glRotatef((GLfloat) arm_angles[ELBOW_Z], 0., 0., 1.);
//        glTranslatef(1., 0., 0.);
//        glPushMatrix();
//            glScalef(2.0, 0.4, 1.0);
//            glColor3f(249./255., 238./255., 153./255.);
//            glutWireCube(1.);       // elbow
//        glPopMatrix();
//    
//        glTranslatef(1., 0., 0.);
//        glRotatef((GLfloat) arm_angles[WRIST_Z], 0., 0., 1.);
//        glRotatef((GLfloat) arm_angles[WRIST_X], 1., 0., 0.);
//
//        glTranslatef(1., 0., 0.);
//        glPushMatrix();
//            glScalef(2.0, 0.4, 1.0);
//            glColor3f(207./255., 106./255., 76./255.);
//            glutWireCube(1.);       // wrist
//        glPopMatrix();
//    glPopMatrix();
//    
//    // Ejecutar los comandos 
//    glutSwapBuffers();
//}
//
//
//// Se llama cuando cambia el tamaño de la ventana
//void reshape(GLsizei w, GLsizei h) {
//    // Tamanyo del viewport
//	glViewport(0, 0, w, h);
//    
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 300.0);
//    
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//// Responder a los eventos de teclas especiales
//void specialKeys(int key, int x, int y) {
//    GLfloat distanceDelta = 1.0, angleDelta = 5 * M_PI / 180.0;
//    if(key == GLUT_KEY_UP) {
//        cameraDistance -= distanceDelta;
//        cameraDistance = max((GLfloat)2.0, cameraDistance);
//    }
//    if(key == GLUT_KEY_DOWN) {
//        cameraDistance += distanceDelta;
//    }
//    if(key == GLUT_KEY_LEFT) {
//        cameraAngle -= angleDelta;
//    }
//    if(key == GLUT_KEY_RIGHT) {
//        cameraAngle += angleDelta;
//    }
//    glutPostRedisplay();
//}
//
//void keyboard(unsigned char key, int x, int y) {
//    int delta = 5;
//
//    switch (key) {
//        case 27: //ESC
//            exit(0);
//        case 'q':
//            change_angle(SHOULDER_Y, delta, -180, 0);
//            break;
//        case 'a':
//            change_angle(SHOULDER_Y, -delta, -180, 0);
//            break;
//        case 'w':
//            change_angle(SHOULDER_Z, delta, -90, 90);
//            break;
//        case 's':
//            change_angle(SHOULDER_Z, -delta, -90, 90);
//            break;
//        case 'e':
//            change_angle(ELBOW_Z, delta, 0, 135);
//            break;
//        case 'd':
//            change_angle(ELBOW_Z, -delta, 0, 135);
//            break;
//        case 'r':
//            change_angle(WRIST_X, delta, -45, 45);
//            break;
//        case 'f':
//            change_angle(WRIST_X, -delta, -45, 45);
//            break;
//        case 't':
//            change_angle(WRIST_Z, delta, -15, 90);
//            break;
//        case 'g':
//            change_angle(WRIST_Z, -delta, -15, 90);
//            break;
//    }
//    glutPostRedisplay();
//}
//
//
//// Programa Principal
//int main(int argc, char * argv[]) {
//    glutInit(&argc, argv);    
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize(700, 700);
//    glutCreateWindow("Brazo Robot");
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//    glutSpecialFunc(specialKeys);
//    glutKeyboardFunc(keyboard);
//
//    // Inicialización
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Negro
//    
//    glutMainLoop();
//}
//
