
#include <bits/stdc++.h>
#include <GL/glut.h>

#define F first
#define S second

typedef float Matrix4x4[4][4];

using namespace std;

float X1, Y1, X2, Y2, XMax, XMin, YMax, YMin;

void Init()
{
    glClearColor(1.0, 1.0, 1.0, 0); // Clear color: Black
    glColor3f(0.0, 0.0, 0.0);       // Fill color: White
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    // The original line
    glVertex2f(X1, Y1);
    glVertex2f(X2, Y2);

    // The bounding boc
    glVertex2f(XMin, YMin);
    glVertex2f(XMin, YMax);
    glVertex2f(XMin, YMax);
    glVertex2f(XMax, YMax);
    glVertex2f(XMax, YMax);
    glVertex2f(XMax, YMin);
    glVertex2f(XMax, YMin);
    glVertex2f(XMin, YMin);

    glEnd();
    glFlush();
}

void clippedLine(double u1, double u2)
{
    double deltaX = X2 - X1;
    double deltaY = Y2 - Y1;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    // Display the bounding box
    glVertex2f(XMin, YMin);
    glVertex2f(XMin, YMax);
    glVertex2f(XMin, YMax);
    glVertex2f(XMax, YMax);
    glVertex2f(XMax, YMax);
    glVertex2f(XMax, YMin);
    glVertex2f(XMax, YMin);
    glVertex2f(XMin, YMin);

    // Display the clipped line
    glVertex2f(X1 + deltaX * u1, Y1 + deltaY * u1);
    glVertex2f(X1 + deltaX * u2, Y1 + deltaY * u2);
    glEnd();
    glFlush();
}

void LiangBarsky()
{
    double deltaX = X2 - X1;
    double deltaY = Y2 - Y1;

    vector<double> p;
    p.push_back(deltaX);
    p.push_back(-deltaX);
    p.push_back(deltaY);
    p.push_back(-deltaY);

    vector<double> q;
    q.push_back(XMax - X1);
    q.push_back(X1 - XMin);
    q.push_back(YMax - Y1);
    q.push_back(Y1 - YMin);

    // u1 and u2 are the parameters corresponding to the clipping points for A1 and A2 (minimum and maximum)
    double u1 = 0, u2 = 1;
    for (int i = 0; i < 4; ++i)
    {
        if (p[i] < 0)
            u1 = max(u1, q[i] / p[i]);
        else if (p[i] > 0)
            u2 = min(u2, q[i] / p[i]);
        else if (q[i] < 0)
        {
            cout << "Line is outside the clipping window.\n";
            return;
        }
    }

    if (u1 > u2)
    {
        cout << "Line is outside the clipping window.\n";
        return;
    }
    else
        clippedLine(u1, u2);
}

void keyboardClip(unsigned char key, int _x, int _y)
{
    if (key == 'c')
    {
        glFlush();
        LiangBarsky();
    }
}

int main(int argc, char **argv)
{
    cout << "Enter the coordinates of the first point of a line (X1,Y1): \n";
    cin >> X1 >> Y1;
    cout << "Enter the coordinates of the second point of a line (X1,Y1): \n";
    cin >> X2 >> Y2;
    cout << "Enter the XMin and XMax of clipping window :\n";
    cin >> XMin >> XMax;
    cout << "Enter the YMin and YMax of clipping window :\n";
    cin >> YMin >> YMax;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(700, 7000);
    glutCreateWindow("Liang Barsky Line Clipping");
    Init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardClip);
    glutMainLoop();
    return 0;
}
