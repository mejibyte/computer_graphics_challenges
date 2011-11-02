#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#include "RgbImage.h"

using namespace std;

// Light properties
GLfloat ambientColor[] = {0.7f, 0.7f, 0.7f, 1.0f}; //Color(0.2, 0.2, 0.2)

GLfloat light0color[]    = { 1.0, 1.0, 1.0, 0.0 };
GLfloat light0position[] = { 10.0, 5.0, 15.0, 0.0 };		// x, y, z, 1:directional 0:point

// Texture handler
GLuint texture;


// Camera settings
GLfloat cameraDistance = 12, cameraAngle = 0;

// angles = { Y rotation at shoulder, Z rotation at shoulder, Z rotation at elbow, X rotation at wrist }
int arm_angles[5] = {0, 0, 0, 0, 0};
enum { SHOULDER_Y, SHOULDER_Z, ELBOW_Z, WRIST_X, WRIST_Z };

void change_angle(int angle, int delta, int minimum = 0, int maximum = 180) {
    arm_angles[angle] = (arm_angles[angle] + delta) % 360;
    arm_angles[angle] = max(arm_angles[angle], minimum);
    arm_angles[angle] = min(arm_angles[angle], maximum);
}

void solidCubeWithTexture(GLfloat size){
    static GLfloat n[6][3] =
    {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] =
    {
        {0, 1, 2, 3},
        {3, 2, 6, 7},
        {7, 6, 5, 4},
        {4, 5, 1, 0},
        {5, 6, 2, 1},
        {7, 4, 0, 3}
    };
    GLfloat v[8][3];
    GLint i;
    
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;
    
    for (i = 5; i >= 0; i--) {
        glBegin(GL_QUADS);
        glNormal3fv(&n[i][0]);
        


        glTexCoord2d(0.0,0.0);
        glVertex3fv(&v[faces[i][0]][0]);
        glTexCoord2d(0.0,1.0);
        glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2d(1.0,1.0);        
        glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2d(1.0,0.0);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

// Desplegar la escena 3D
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    
    GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat mat_blue[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat low_shininess[] = { 2.0 };
    
    glLoadIdentity();
    GLfloat x = cameraDistance * sin(cameraAngle);
    GLfloat z = cameraDistance * cos(cameraAngle);
    gluLookAt (x, 0.0, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);    
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0color);
    glLightfv(GL_LIGHT0, GL_POSITION, light0position);
    
    glPushMatrix();
    glRotatef((GLfloat) arm_angles[SHOULDER_Y], 0., 1., 0.);
    glRotatef((GLfloat) arm_angles[SHOULDER_Z], 0., 0., 1.);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_blue);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
    
    glTranslatef(1., 0., 0.);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    solidCubeWithTexture(1.);       // shoulder
    glPopMatrix();
    
    glTranslatef(1., 0., 0.);
    glRotatef((GLfloat) arm_angles[ELBOW_Z], 0., 0., 1.);
    glTranslatef(1., 0., 0.);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glColor3f(249./255., 238./255., 153./255.);
    solidCubeWithTexture(1.);       // elbow
    glPopMatrix();
    
    glTranslatef(1., 0., 0.);
    glRotatef((GLfloat) arm_angles[WRIST_Z], 0., 0., 1.);
    glRotatef((GLfloat) arm_angles[WRIST_X], 1., 0., 0.);
    
    glTranslatef(1., 0., 0.);
    glPushMatrix();
    
    glScalef(2.0, 0.4, 1.0);
    glColor3f(207./255., 106./255., 76./255.);
    glTexCoord2f(0.0, 0.0);    
    solidCubeWithTexture(1.);       // wrist
    glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
    glDisable(GL_TEXTURE_2D);    
}


// Se llama cuando cambia el tamaño de la ventana
void reshape(GLsizei w, GLsizei h) {
    // Tamanyo del viewport
	glViewport(0, 0, w, h);
    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 300.0);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Responder a los eventos de teclas especiales
void specialKeys(int key, int x, int y) {
    GLfloat distanceDelta = 1.0, angleDelta = 5 * M_PI / 180.0;
    if(key == GLUT_KEY_UP) {
        cameraDistance -= distanceDelta;
        cameraDistance = max((GLfloat)2.0, cameraDistance);
    }
    if(key == GLUT_KEY_DOWN) {
        cameraDistance += distanceDelta;
    }
    if(key == GLUT_KEY_LEFT) {
        cameraAngle -= angleDelta;
    }
    if(key == GLUT_KEY_RIGHT) {
        cameraAngle += angleDelta;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    int delta = 5;
    
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
            change_angle(WRIST_X, delta, -45, 45);
            break;
        case 'f':
            change_angle(WRIST_X, -delta, -45, 45);
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

/*
 * Read a texture map from a BMP bitmap file.
 */
void loadTextureFromFile(char *filename)
{    
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
    
	RgbImage theTexMap( filename );
    
	// Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
	//    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3,theTexMap.GetNumCols(), theTexMap.GetNumRows(),
                      GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
    
}


GLuint loadTexture( const char * filename, bool wrap ) {
    GLuint ans;

    glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
    RgbImage theTexMap( filename );

    
    // allocate a texture name
    glGenTextures( 1, &ans );
    
    // select our current texture
    glBindTexture( GL_TEXTURE_2D, ans );
    
    // select modulate to mix texture with color for shading
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    
    // when texture area is small, bilinear filter the closest mipmap
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    wrap ? GL_REPEAT : GL_CLAMP );
    
    // build our texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3,theTexMap.GetNumCols(), theTexMap.GetNumRows(),
                      GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
    
    return ans;
}

void init(){
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    texture = loadTexture("tex_wood.bmp", true);
}

// Programa Principal
int main(int argc, char * argv[]) {
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Brazo Robot");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    
    // Inicialización
    init();
    glutMainLoop();
    glDeleteTextures( 1, &texture );    
}

