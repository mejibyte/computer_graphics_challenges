/*
 * TextureBMP.cpp
 *
 * Loosely based on the example checker.c 
 * (Example 9-1, OpenGL Programming Guide, 3rd edition) 
 * 
 * Read an image from a bitmap (.bmp) file, and draw it as a texture 
 * map on a quad.  A cpp class RgbImage is used to read a texture
 * map from a bitmap (.bmp) file.
 *
 * Author: Samuel R. Buss
 *
 * Software accompanying the book.
 *		3D Computer Graphics: A Mathematical Introduction with OpenGL,
 *		by S. Buss, Cambridge University Press, 2003.
 *
 * Software is "as-is" and carries no warranty.  It may be used without
 *   restriction, but if you modify it, please change the filenames to
 *   prevent confusion between different versions.
 * Bug reports: Sam Buss, sbuss@ucsd.edu.
 * Web page: http://math.ucsd.edu/~sbuss/MathCG
 *
 */
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include <cstdlib>
#include "RgbImage.h"

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

/*
 * Draw the texture in the OpenGL graphics window
 */
void drawScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   glLoadIdentity();
   glTranslated(0, 0, 10);
   glRotated(35, 0, 0, 1);
   glRotated(35, 1, 0, 0);
    
   glBegin(GL_QUADS);
   
   glTexCoord2f(0.0, 0.0); 
   glVertex3f(-1.0, -1.0, 0.0);
   
   glTexCoord2f(0.0, 1.0); 
   glVertex3f(-1.0, 1.0, 0.0);
   
   glTexCoord2f(1.0, 1.0); 
   glVertex3f(1.0, 1.0, 0.0);
   
   glTexCoord2f(1.0, 0.0); 
   glVertex3f(1.0, -1.0, 0.0);
   
   glEnd();

   glFlush();
   glDisable(GL_TEXTURE_2D);
}

void resizeWindow(int w, int h)
{
	float viewWidth = 1.1;
	float viewHeight = 1.1;
	glViewport(0, 0, w, h);
	h = (h==0) ? 1 : h;
	w = (w==0) ? 1 : w;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if ( h < w ) {
		viewWidth *= (float)w/(float)h; 
	}
	else {
		viewHeight *= (float)h/(float)w;
	}
	glOrtho( -viewWidth, viewWidth, -viewHeight, viewHeight, -10.0, 10.0 );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 27:
			exit(0);
			break;
		default:
			break;
   }
}

char* filename = "RedLeavesTexture.bmp";

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(240, 240);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	loadTextureFromFile( filename );
	
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resizeWindow);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0; 
}
