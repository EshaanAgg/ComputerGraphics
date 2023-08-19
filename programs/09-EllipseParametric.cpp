#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int X, Y, a, b;

/*
 * Disadvantages:
 * For large a and b, pixelation occurs due to large increase in arc length
 * Rounding off of the coordinates is done to fit the pixel grid
 */

void draw(int xi, int yi)
{
    glVertex2i(X + xi, Y + yi);
    glVertex2i(X + xi, Y - yi);
    glVertex2i(X - xi, Y + yi);
    glVertex2i(X - xi, Y - yi);
}

void ellipse()
{
    glBegin(GL_POINTS);
    for (int i = 0; i <= 90; i++)
    {
        float theta = (i / 180.0) * acos(-1);
        int xi = a * cos(theta), yi = b * sin(theta);
        draw(xi, yi);
    }
    glEnd();
}

void drawEllipse()
{
    glClear(GL_COLOR_BUFFER_BIT);
    ellipse();
    glFlush();
}

void init()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Parametric Ellipse");
    glClearColor(1.0, 1.0, 1.0, 0);
    glColor3f(0, 0, 0);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
    printf("Enter X, Y, a and b for the ellipse.\n");
    scanf("%d %d %d %d", &X, &Y, &a, &b);
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(drawEllipse);
    glutMainLoop();
    return 0;
}