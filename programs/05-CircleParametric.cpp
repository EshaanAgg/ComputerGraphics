#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int X, Y, r;

/*
 * Disadvantage: For large R, pixelation occurs due to large increase in arc length
 * 2. Uneven distribution of brightness (points) due to sinosoidal nature of the parametric representation.
 */

void draw(int X1, int Y1, int xi, int yi)
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

void circle(int X1, int Y1, int r)
{
    glBegin(GL_POINTS);
    for (int i = 0; i <= 45; i++)
    {
        float theta = (i / 180.0) * acos(-1);
        int xi = r * cos(theta), yi = r * sin(theta);
        draw(X, Y, xi, yi);
    }
    glEnd();
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    circle(X, Y, r);
    glFlush();
}

void init()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Parametric Circle");
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
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}