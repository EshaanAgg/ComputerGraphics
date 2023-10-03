
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

    // The bounding box
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

void CyrusBeck()
{
    auto p1 = make_pair(X1, Y1);
    auto p2 = make_pair(X2, Y2);

    // We manually define the normal vectors corresponding to the four sides of the clipping rectange in our case
    // We also choose a point on each of them
    vector<pair<double, double>> n;
    vector<pair<double, double>> f;
    n.push_back({1, 0});
    n.push_back({-1, 0});
    n.push_back({0, 1});
    n.push_back({0, -1});
    f.push_back({XMin, YMin});
    f.push_back({XMax, YMax});
    f.push_back({XMin, YMin});
    f.push_back({XMax, YMax});

    // tl and tu are the parameters corresponding to the clipping points for A1 and A2 (minimum and maximum)
    double tl = 0, tu = 1;
    // Corresponds to the P0-P1 vector
    auto D = make_pair(X2 - X1, Y2 - Y1);
    for (int i = 0; i < 4; i++)
    {
        // Corresponds to the P0-P(t) vector
        auto w = make_pair(X1 - f[i].F, Y1 - f[i].S);
        double DdotN = D.F * n[i].F + D.S * n[i].S;
        double WdotN = w.F * n[i].F + w.S * n[i].S;
        if (DdotN != 0.0)
        {
            double t = -WdotN / DdotN;
            if (DdotN > 0.0)
            {
                if (t > 1)
                {
                    cout << "Line is outside the clipping window.\n";
                    return;
                }
                tl = max(t, tl);
            }
            else
            {
                if (t < 0)
                {
                    cout << "Line is outside the clipping window.\n";
                    return;
                }
                tu = min(t, tu);
            }
        }
        else
        {
            if (WdotN < 0.0)
            {
                cout << "Line is outside the clipping window.\n";
                return;
            }
        }
    }

    if (tl > tu)
        cout << "Line is outside the clipping window.\n";
    else
    {
        cout << tl << " " << tu << "\n";
        clippedLine(tl, tu);
    }
}

void keyboardClip(unsigned char key, int _x, int _y)
{
    if (key == 'c')
    {
        glFlush();
        CyrusBeck();
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
    glutCreateWindow("Cyrus Beck Line Clipping");
    Init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardClip);
    glutMainLoop();
    return 0;
}
