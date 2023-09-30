#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

void display();
using namespace std;

float XMin = -100, YMin = -100, XMax = 100, YMax = 100;
float xd1, yd1, xd2, yd2;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 600, 0, 600);
}

int code(float x, float y)
{
    int c = 0;
    if (y > YMax)
        c = 8;
    else if (y < YMin)
        c = 4;
    if (x > XMax)
        c = c | 2;
    else if (x < XMin)
        c = c | 1;
    return c;
}

void cohenLine(float x1, float y1, float x2, float y2)
{
    int c1 = code(x1, y1);
    int c2 = code(x2, y2);
    float m = (y2 - y1) / (x2 - x1);

    // While the line is not completely inside the window
    while ((c1 | c2) != 0)
    {
        // Line is outside the window and not visible, so we can exit
        if ((c1 & c2) != 0)
            exit(0);

        // Create temporary copies of the variables for the first endpoint
        float xi = x1;
        float yi = y1;
        int c = c1;

        // If A1 is inside the window, A2 must be the clipping reason, so which the point
        if (c == 0)
        {
            c = c2;
            xi = x2;
            yi = y2;
        }

        // Calculate the intersection with the boundaries
        float x, y;
        // Top of the window
        if ((c & 8) > 0)
        {
            y = YMax;
            x = xi + 1.0 / m * (YMax - yi);
        }
        // Bottom of the window
        else if ((c & 4) > 0)
        {
            y = YMin;
            x = xi + 1.0 / m * (YMin - yi);
        }
        // Right boundary
        else if ((c & 2) > 0)
        {
            x = XMax;
            y = yi + m * (XMax - xi);
        }
        // Left boundary
        else if ((c & 1) > 0)
        {
            x = XMin;
            y = yi + m * (XMin - xi);
        }

        // Replace the intial coordinates with the new coordinates
        if (c == c1)
        {
            xd1 = x;
            yd1 = y;
            c1 = code(xd1, yd1);
        }
        else if (c == c2)
        {
            xd2 = x;
            yd2 = y;
            c2 = code(xd2, yd2);
        }
    }

    display();
}

void clipLine(unsigned char key, int x, int y)
{
    if (key == 'c')
    {
        cohenLine(xd1, yd1, xd2, yd2);
        glFlush();
    }
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_LINE_LOOP);
    glVertex2i(XMin, YMin);
    glVertex2i(XMin, YMax);
    glVertex2i(XMax, YMax);
    glVertex2i(XMax, YMin);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(xd1, yd1);
    glVertex2i(xd2, yd2);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    cout << "Enter the coordinates of the first point of a line (x1,y1): \n";
    cin >> xd1 >> yd1;
    cout << "Enter the coordinates of the second point of a line (x1,y1): \n";
    cin >> xd2 >> yd2;
    cout << "Enter the XMIN and XMAX of clipping window:\n";
    cin >> XMin >> XMax;
    cout << "Enter the YMin and YMax of clipping window:\n";
    cin >> YMin >> YMax;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cohen Sutherland Clipping");
    glutDisplayFunc(display);
    glutKeyboardFunc(clipLine);
    init();
    glutMainLoop();
    return 0;
}