#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

using namespace std;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

// Specify the rotation of the cube in the X-Y axes
GLfloat xRot = 0.0;
GLfloat yRot = 0.0;

// Draws a cube with 6 different coloured faces
void drawCube()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glShadeModel(GL_FLAT);
    glFrontFace(GL_CW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();

    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(50.0f, 50.0f, 50.0f);
    glVertex3f(-50.0f, 50.0f, 50.0f);
    glVertex3f(-50.0f, -50.0f, 50.0f);
    glVertex3f(50.0f, -50.0f, 50.0f);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(50.0, 50.0, -50.0);
    glVertex3f(50.0, 50.0, 50.0);
    glVertex3f(50.0, -50.0, 50.0);
    glVertex3f(50.0, -50.0, -50.0);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(50.0, -50.0, -50.0);
    glVertex3f(-50.0, -50.0, -50.0);
    glVertex3f(-50.0, 50.0, -50.0);
    glVertex3f(50.0, 50.0, -50.0);

    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-50.0, 50.0, 50.0);
    glVertex3f(-50.0, 50.0, -50.0);
    glVertex3f(-50.0, -50.0, -50.0);
    glVertex3f(-50.0, -50.0, 50.0);

    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(50.0, 50.0, -50.0);
    glVertex3f(-50.0, 50.0, -50.0);
    glVertex3f(-50.0, 50.0, 50.0);
    glVertex3f(50.0, 50.0, 50.0);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(50.0, -50.0, 50.0);
    glVertex3f(-50.0, -50.0, 50.0);
    glVertex3f(-50.0, -50.0, -50.0);
    glVertex3f(50.0, -50.0, -50.0);

    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

// Map the keypresses to rotation of the cube
void actionKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
        xRot -= 5.0f;
    else if (key == GLUT_KEY_DOWN)
        xRot += 5.0f;
    else if (key == GLUT_KEY_RIGHT)
        yRot -= 5.0f;
    else if (key == GLUT_KEY_LEFT)
        yRot += 5.0f;
    else if (key > 356.0f)
        xRot = 0.0f;
    else if (key < -1.0f)
        xRot = 355.0f;
    else if (key > 356.0f)
        yRot = 0.0f;
    else if (key < -1.0f)
        yRot = 355.0f;
    else
        exit(0);
    glutPostRedisplay();
}

void keyboardAction(unsigned char key, int x, int y)
{
    exit(0);
}

// The reshaping function which is used to change the orthographic projection matrix on the basis of the supplied height `h` and width `w`
void changeSize(int w, int h)
{
    GLfloat nRange = 100.0f;
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
    else
        glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Scan Line Z Buffer");
    glViewport(0, 0, 500, 500);

    glutReshapeFunc(changeSize);
    glutKeyboardFunc(keyboardAction);
    glutSpecialFunc(actionKeys);
    glutDisplayFunc(drawCube);

    init();

    glutMainLoop();

    return 0;
}