#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>


GLfloat ctrlpoints[4][4][3] =
{
    {
        {-1.5, -1.5, 4.0},
        {-0.5, -1.5, 2.0},
        {0.5, -1.5, -1.0},
        {1.5, -1.5, 2.0}},
    {
        {-1.5, -0.5, 1.0},
        {-0.5, -0.5, 3.0},
        {0.5, -0.5, 0.0},
        {1.5, -0.5, -1.0}},
    {
        {-1.5, 0.5, 4.0},
        {-0.5, 0.5, 0.0},
        {0.5, 0.5, 3.0},
        {1.5, 0.5, 4.0}},
    {
        {-1.5, 1.5, -2.0},
        {-0.5, 1.5, -2.0},
        {0.5, 1.5, 0.0},
        {1.5, 1.5, -1.0}}
};

void 
myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(85.0, 1.0, 1.0, 1.0);
    glEvalMesh2(GL_LINE, 0, 20, 0, 20);
    glPopMatrix();
    glFlush();
}

void 
myinit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_MAP2_VERTEX_3);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
            0, 1, 12, 4, &ctrlpoints[0][0][0]);    
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
}

void 
myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4.0, 4.0, -4.0 * (GLfloat) h / (GLfloat) w,
                4.0 * (GLfloat) h / (GLfloat) w, -4.0, 4.0);
    else
        glOrtho(-4.0 * (GLfloat) w / (GLfloat) h,
                4.0 * (GLfloat) w / (GLfloat) h, -4.0, 4.0, -4.0, 4.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int 
_main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}
