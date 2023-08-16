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
    int d = 3 - 2 * r;
    draw(x, y);

    while (x <= y)
    {
        if (d < 0)
        {
            x++;
            draw(x, y);
            d = d + 4 * x + 6;
        }
        else
        {
            x++;
            y--;
            draw(x, y);
            d = d + 4 * (x - y) + 10;
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
    glutCreateWindow("Breshenham's Circle");
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