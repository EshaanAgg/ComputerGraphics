#include <bits/stdc++.h>
#include <GL/glut.h>

typedef long long ll;
typedef long double ld;

#define F first
#define S second

using namespace std;

float X1, Y1, X2, Y2, XMax, XMin, YMax, YMin;

// Storing the clipping polygon
vector<pair<int, int>> vertices;

void Init()
{
    glClearColor(1.0, 1.0, 1.0, 0); // Clear color: Black
    glColor3f(0.0, 0.0, 0.0);       // Fill Color : White
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    // Draw the bounding box
    glVertex2f(XMin, YMin);
    glVertex2f(XMin, YMax);
    glVertex2f(XMin, YMax);
    glVertex2f(XMax, YMax);
    glVertex2f(XMax, YMax);
    glVertex2f(XMax, YMin);
    glVertex2f(XMax, YMin);
    glVertex2f(XMin, YMin);

    // Draw the bounding polygon
    for (int i = 0; i < 4; i++)
    {
        glVertex2f(vertices[i].F, vertices[i].S);
        glVertex2f(vertices[(i + 1) % 4].F, vertices[(i + 1) % 4].S);
    }
    glEnd();
    glFlush();
}

// Draw the clipped line
void clippedLine(double u1, double u2)
{
    double deltaX = X2 - X1;
    double deltaY = Y2 - Y1;
    glBegin(GL_LINES);
    glVertex2f(X1 + deltaX * u1, Y1 + deltaY * u1);
    glVertex2f(X1 + deltaX * u2, Y1 + deltaY * u2);
    glEnd();
}

// Use Liang Barsky to perform the line clipping in polygon clipping
void polygonClipping()
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

    double u1 = 0, u2 = 1;
    for (int i = 0; i < 4; ++i)
    {
        if (p[i] < 0)
            u1 = max(u1, q[i] / p[i]);
        else if (p[i] > 0)
            u2 = min(u2, q[i] / p[i]);
        else if (q[i] < 0)
        {
            cout << "Line outside the clipping window\n";
            return;
        }
    }

    if (u1 > u2)
    {
        cout << "Line outside the clipping window\n";
        return;
    }
    else
        clippedLine(u1, u2);
}

void myKey(unsigned char key, int x, int y)
{
    if (key == 'c')
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINES);
        glVertex2f(XMin, YMin);
        glVertex2f(XMin, YMax);
        glVertex2f(XMin, YMax);
        glVertex2f(XMax, YMax);
        glVertex2f(XMax, YMax);
        glVertex2f(XMax, YMin);
        glVertex2f(XMax, YMin);
        glVertex2f(XMin, YMin);
        glEnd();
        for (int i = 0; i < 4; i++)
        {
            X1 = vertices[i].F;
            Y1 = vertices[i].S;
            X2 = vertices[(i + 1) % 4].F;
            Y2 = vertices[(i + 1) % 4].S;
            polygonClipping();
        }
        glFlush();
    }
}

int main(int argc, char **argv)
{
    int n = 4;
    cout << "Enter the four vertices :\n";
    for (int i = 0; i < 4; ++i)
    {
        pair<int, int> c;
        cin >> c.F >> c.S;
        vertices.push_back(c);
    }

    cout << "Enter the XMin and XMax of clipping window :\n";
    cin >> XMin >> XMax;
    cout << "Enter the YMin and YMax of clipping window :\n";
    cin >> YMin >> YMax;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(700, 7000);
    glutCreateWindow("Polygon Clipping");
    Init();
    glutDisplayFunc(display);
    glutKeyboardFunc(myKey);
    glutMainLoop();
    return 0;
}
