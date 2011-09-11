#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

GLfloat angle, fAspect;
static int shoulder = 0, elbow = 0;

void elbowAdd() {
    elbow = (elbow + 5) % 360;     
}

void elbowSubtract() {
    elbow = (elbow - 5) % 360;     
}

void shoulderAdd() {
    shoulder = (shoulder + 5) % 360;     
}

void shoulderSubtract() {
    shoulder = (shoulder - 5) % 360;     
}

// Desplegar la escena 3D
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
    
	glColor3f(1.0f, 1.0f, 1.0f);
    
	glPushMatrix();
    //glTranslatef(-1., 0., 0.);
    glRotatef((GLfloat) shoulder, 0., 0., 1.);
    glTranslatef(1., 0., 0.);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.);       // shoulder
    glPopMatrix();
    
    glTranslatef(1., 0., 0.);
    glRotatef((GLfloat) elbow, 0., 0., 1.);
    glTranslatef(1., 0., 0.);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.);       // elbow
    glPopMatrix();
    glPopMatrix();
	// Ejecutar los comandos 
	glutSwapBuffers();
}

// Inicializar los parametros de despliegue
void init (void)
{ 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    angle=45;
}

// Especificar los parametros de visualizacion
void visualizationParams(void)
{
	// Sistema de coordenadas de proyeccion
	glMatrixMode(GL_PROJECTION);
	// Inicializa el sistema de coordenadas de la proyeccion
	glLoadIdentity();
    
	// Especifica proyeccion perspectiva
	gluPerspective(angle,fAspect,0.1,500);
    
	// Especifica el sistema de coordenadas del modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa el sistema de coordenadas del modelo
	glLoadIdentity();
    
	// Especifica la posicion del observador
	// Posicion del ojo, hacia donde mira, vector arriba
	gluLookAt(0,0,15, 0,0,0, 0,1,0);
}

// Se llama cuando cambia el tamanyo de la ventana
void reshape(GLsizei w, GLsizei h)
{
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
        elbowAdd();
    }
    if(key == GLUT_KEY_DOWN) {
        elbowSubtract();
    }
    if(key == GLUT_KEY_LEFT) {
        shoulderAdd();
    }
    if(key == GLUT_KEY_RIGHT) {
        shoulderSubtract();
    }
    glutPostRedisplay();
}
// Programa Principal
int main(int argc, char * argv[])
{
    glutInit(&argc, argv);    
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("Brazo Robot");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialKeys);
	init();
	glutMainLoop();
}

