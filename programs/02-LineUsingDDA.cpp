#include <iostream>
#include <math.h>
#include <GL/glut.h>

double X1, X2, Y1, Y2;

float roundValue(float v)
{
    return floor(v + 0.5);
}

void lineDDA()
{
    // Slope and steps calculation
    double dx = X2 - X1;
    double dy = Y2 - Y1;
    double steps;
    float xInc, yInc, x = X1, y = Y1;

    steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    xInc = dx / (float)steps;
    yInc = dy / float(steps);

    // Drawing the line on the board
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);

    glVertex2d(x, y);
    for (int k = 0; k < steps; k++)
    {
        x += xInc;
        y += yInc;
        glVertex2d(roundValue(x), roundValue(y));
    }
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

using namespace std;

int main(int argc, char **argv)
{
    cout << "Enter Endpoints (x1, y1, x2, y2):\n";
    cin >> X1 >> Y1 >> X2 >> Y2;

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Line");

    Init();

    glutDisplayFunc(lineDDA);
    glutMainLoop();

    return 0;
}