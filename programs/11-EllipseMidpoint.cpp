#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int X, Y, a, b;

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

    // Lower half in the first quadrant
    int x = 0;
    int y = b;
    float d = b * b - a * a * b + (a * a) / 4;
    while (x <= ((y * a * a) / (b * b)))
    {
        draw(x, y);
        if (d < 0)
        {
            x++;
            d += 2 * b * b * (2 * x + 3);
        }
        else
        {
            y--;
            x++;
            d += 2 * b * b * (2 * x + 3) - 4 * (a * a * y + a * a);
        }
    }

    // Upper half in the first quadrant
    x = a;
    y = 0;
    d = b * b - a * a * b + (a * a) / 4;
    while (x > ((y * a * a) / (b * b)))
    {
        draw(x, y);
        if (d < 0)
        {
            y++;
            d += 2 * a * a * (2 * y + 3);
        }
        else
        {
            y++;
            x--;
            d += 2 * a * a * (2 * y + 3) - 4 * (b * b * x + b * b);
        }
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
    glutCreateWindow("Midpoint Ellipse");
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