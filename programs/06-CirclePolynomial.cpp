#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int X, Y, r;

/*
 * Disadvantages:
 * Uneven distirbution of the points leads to different brightness levels
 * The upper and lower arcs have higher brightness, while the side arcs are fainter
 */

void draw(int xi, int yi)
{
    glVertex2i(X + xi, Y + yi);
    glVertex2i(X + xi, Y - yi);
    glVertex2i(X - xi, Y + yi);
    glVertex2i(X - xi, Y - yi);
    glVertex2i(X + yi, Y + xi);
    glVertex2i(X + yi, Y - xi);
    glVertex2i(X - yi, Y + xi);
    glVertex2i(X - yi, Y - xi);
}

void circle()
{
    glBegin(GL_POINTS);
    for (int x = 0; x < (int)((float)r / sqrt(2)); x++)
    {
        int y = sqrt(r * r - x * x);
        draw(x, y);
    }
    glEnd();
}

void drawCircle()
{
    glClear(GL_COLOR_BUFFER_BIT);
    circle();
    glFlush();
}

void init()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Polynomial Circle");
    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3f(0, 0, 0);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
    printf("Enter X, Y and R.\n");
    scanf("%d %d %d", &X, &Y, &r);
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(drawCircle);
    glutMainLoop();
    return 0;
}