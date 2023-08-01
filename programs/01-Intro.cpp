#include <GL/glut.h>

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2d(-0.5f, 0.0f);
    glVertex2d(0.5f, 0.0f);
    glVertex2d(0.0f, 1.0f);
    glEnd();
    glFlush();
}

void Init()
{
    // Init the window to be displayed
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Demo");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}