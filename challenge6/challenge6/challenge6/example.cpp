/*
 *  pyramidWithMaterial
 *  This program demonstrates how to create a sphere and a plane,
 *  with color and lights.
 */
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>

namespace Example {
    GLfloat distance = 5.0;
    GLfloat increment = 0.1;
    GLfloat angle = 0.0;
    GLfloat angleIncrement = 0.1;
    
    // Light properties
    GLfloat ambient[] = { 0.0, 0.0, 0.0, 0.0 };	
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat position[] = { 5.0, 5.0, 5.0, 0.0 };		// x, y, z, 1:directional 0:point

    void _init(void) 
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

    void _display(void)
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

    void _reshape (int w, int h)
    {
        glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
        glMatrixMode (GL_PROJECTION);
        glLoadIdentity ();
        // parameters for glFrustrum: left, rigth, bottom, top, near, far
        glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
        glMatrixMode (GL_MODELVIEW);
    }

    void _keyboard(unsigned char key, int x, int y)
    {
        switch (key) {
            case 27:
                exit(0);
                break;
            case 'w':		
                //Camera.MoveForwards( -0.1 ) ;
                distance -= increment;
                _display();
                break;
            case 's':		
                //Camera.MoveForwards( 0.1 ) ;
                distance += increment;
                _display();
                break;
            case 'a':		
                //Camera.turnLeft ;
                angle -= angleIncrement;
                _display();
                break;
            case 'd':		
                //Camera.turnRight ;
                angle += angleIncrement;
                _display();
                break;
        }
    }

    int _main(int argc, char** argv)
    {
        glutInit(&argc, argv);
        glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize (500, 500); 
        glutInitWindowPosition (100, 100);
        glutCreateWindow (argv[0]);
        _init ();
        glutDisplayFunc(_display); 
        glutReshapeFunc(_reshape);
        glutKeyboardFunc(_keyboard);
        glutMainLoop();
        return 0;
    }
}