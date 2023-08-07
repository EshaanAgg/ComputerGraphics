#include <stdlib.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

int X0, Y0, X1, Y1;
const int GAP = 25;

void display()
{
    int x, y, dx, dy, p;

    // Initialise all the variables
    dx = abs(X1 - X0);
    dy = abs(Y1 - Y0);
    x = X0, y = Y0;
    p = 2 * dy - dx;

    // Begin plotting the points
    glBegin(GL_POINTS);

    glVertex2d(x, y);

    for (int k = 0; k < dx; k++)
    {
        if (p < 0)
        {
            if (k % GAP < GAP / 2)
                glVertex2d(x + 1, y);
            x = x + 1;
            p = p + 2 * dy;
        }
        else
        {
            if (k % GAP < GAP / 2)
                glVertex2d(x + 1, y + 1);
            x = x + 1, y = y + 1;
            p = p + 2 * dy - 2 * dx;
        }
    }

    // End plotting the points and print the line
    glEnd();
    glFlush();
}

using namespace std;

int main(int argc, char **argv)
{

    cout << "Value of X0 : ";
    cin >> X0;
    cout << "Value of Y0 : ";
    cin >> Y0;
    cout << "Value of X1 : ";
    cin >> X1;
    cout << "Value of Y1 : ";
    cin >> Y1;

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham's Line Drawing: ");
    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}