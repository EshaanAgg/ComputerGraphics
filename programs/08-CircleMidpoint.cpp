#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int X, Y, r;

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

    int x = 0, y = r;
    int p = 5 / 4 - r;
    draw(x, y);

    while (x <= y)
    {
        if (p < 0)
        {
            x++;
            draw(x, y);
            p = p + 2 * x + 1;
        }
        else
        {
            x++;
            y--;
            draw(x, y);
            p = p + 2 * (x - y) + 1;
        }
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
    glutCreateWindow("Midpoint Circle");
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