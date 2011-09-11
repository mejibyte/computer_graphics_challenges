#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

GLfloat angle, fAspect;

// angles = { Y rotation at shoulder, Z rotation at shoulder, Z rotation at elbow, X rotation at wrist }
int arm_angles[5] = {0, 0, 0, 0, 0};
enum { SHOULDER_Y, SHOULDER_Z, ELBOW_Z, WRIST_X, WRIST_Z };

void change_angle(int angle, int delta, int minimum = 0, int maximum = 180) {
    arm_angles[angle] = (arm_angles[angle] + delta) % 360;
    arm_angles[angle] = max(arm_angles[angle], minimum);
    arm_angles[angle] = min(arm_angles[angle], maximum);
}

// Desplegar la escena 3D
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
        glRotatef((GLfloat) arm_angles[SHOULDER_Y], 0., 1., 0.);
        glRotatef((GLfloat) arm_angles[SHOULDER_Z], 0., 0., 1.);
    
        glTranslatef(1., 0., 0.);
        glPushMatrix();
            glScalef(2.0, 0.4, 1.0);
            glColor3f(1.0f, 1.0f, 1.0f);
            glutWireCube(1.);       // shoulder
        glPopMatrix();

        glTranslatef(1., 0., 0.);
        glRotatef((GLfloat) arm_angles[ELBOW_Z], 0., 0., 1.);
        glTranslatef(1., 0., 0.);
        glPushMatrix();
            glScalef(2.0, 0.4, 1.0);
            glColor3f(249./255., 238./255., 153./255.);
            glutWireCube(1.);       // elbow
        glPopMatrix();
    
        glTranslatef(1., 0., 0.);
        glRotatef((GLfloat) arm_angles[WRIST_Z], 0., 0., 1.);
        glRotatef((GLfloat) arm_angles[WRIST_X], 1., 0., 0.);

        glTranslatef(1., 0., 0.);
        glPushMatrix();
            glScalef(2.0, 0.4, 1.0);
            glColor3f(207./255., 106./255., 76./255.);
            glutWireCube(1.);       // wrist
        glPopMatrix();
    glPopMatrix();
    
    // Ejecutar los comandos 
    glutSwapBuffers();
}

// Especificar los parametros de visualizacion
void visualizationParams(void) {
	// Sistema de coordenadas de proyeccion
	glMatrixMode(GL_PROJECTION);
	// Inicializa el sistema de coordenadas de la proyeccion
	glLoadIdentity();
    
	// Especifica proyeccion perspectiva
	gluPerspective(45,fAspect,0.1,500);
    
	// Especifica el sistema de coordenadas del modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa el sistema de coordenadas del modelo
	glLoadIdentity();
    
	// Especifica la posicion del observador
	// Posicion del ojo, hacia donde mira, vector arriba
	gluLookAt(0,0,18, 0,0,0, 0,1,0);
}

// Se llama cuando cambia el tamaño de la ventana
void reshape(GLsizei w, GLsizei h) {
	// Para prevenir division por 0
	if ( h == 0 ) h = 1;
    
	// Tamanyo del viewport
	glViewport(0, 0, w, h);
    
	// Aspect Ration
	fAspect = (GLfloat)w/(GLfloat)h;
    
	visualizationParams();
}

// Responder a los eventos de teclas especiales
void specialKeys(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
    }
    if(key == GLUT_KEY_DOWN) {
    }
    if(key == GLUT_KEY_LEFT) {
    }
    if(key == GLUT_KEY_RIGHT) {
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    int delta = 9;

    switch (key) {
        case 27: //ESC
            exit(0);
        case 'q':
            change_angle(SHOULDER_Y, delta, -180, 0);
            break;
        case 'a':
            change_angle(SHOULDER_Y, -delta, -180, 0);
            break;
        case 'w':
            change_angle(SHOULDER_Z, delta, -90, 90);
            break;
        case 's':
            change_angle(SHOULDER_Z, -delta, -90, 90);
            break;
        case 'e':
            change_angle(ELBOW_Z, delta, 0, 135);
            break;
        case 'd':
            change_angle(ELBOW_Z, -delta, 0, 135);
            break;
        case 'r':
            change_angle(WRIST_X, delta, -90, 90);
            break;
        case 'f':
            change_angle(WRIST_X, -delta, -90, 90);
            break;
        case 't':
            change_angle(WRIST_Z, delta, -15, 90);
            break;
        case 'g':
            change_angle(WRIST_Z, -delta, -15, 90);
            break;
    }
    glutPostRedisplay();
}


// Programa Principal
int main(int argc, char * argv[]) {
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Brazo Robot");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);

    // Inicialización
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Negro
    
    glutMainLoop();
}

