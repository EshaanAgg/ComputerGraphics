#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;
int N = 6, XMin, YMin, ZMin, XMax, YMax, ZMax, ang = 0;
// Flag controls whether to show the original lines or the transformed lines
// tFlag controls whether to show the animation or not
bool flag = true, tFlag = false;

// Define a point class
class Point
{
public:
    int X, Y, Z;
    Point(int x, int y, int z)
    {
        X = x;
        Y = y;
        Z = z;
    }
    int operator*(Point const &p)
    {
        int res = X * p.X + Y * p.Y + Z * p.Z;
        return res;
    }
};

vector<pair<Point, Point>> orgLines, transformedLines;
vector<Point> vertex, normals;

// Define a timer and redisplay the screen after changing the projection angle
void timer(int value)
{
    ang += 1;
    if (tFlag)
        glutTimerFunc(1000 / 30, timer, 0);
    glutPostRedisplay();
}

// Define the normals and the vertexes chosen on the planes for the algorithm
void initParams()
{
    for (int i = 0; i < N; i++)
    {
        if (i % 2)
            vertex.push_back({XMax, YMax, ZMax});
        else
            vertex.push_back({XMin, YMin, ZMin});
    }

    // The normals corresponding to the 6 faces are hardcoded
    normals.push_back({-1, 0, 0});
    normals.push_back({1, 0, 0});
    normals.push_back({0, 0, -1});
    normals.push_back({0, 0, 1});
    normals.push_back({0, -1, 0});
    normals.push_back({0, 1, 0});
}

void CyrusBeck(pair<Point, Point> l)
{
    Point p1p0(l.second.X - l.first.X, l.second.Y - l.first.Y, l.second.Z - l.first.Z);

    vector<Point> p0pe;
    vector<int> num, den;

    for (int i = 0; i < N; i++)
    {
        int x, y, z;
        x = vertex[i].X - l.first.X;
        y = vertex[i].Y - l.first.Y;
        z = vertex[i].Z - l.first.Z;
        p0pe.push_back({x, y, z});
    }

    for (int i = 0; i < N; i++)
    {
        num.push_back(normals[i] * p0pe[i]);
        den.push_back(normals[i] * p1p0);
    }

    vector<float> tl, te;
    for (int i = 0; i < N; i++)
    {
        float t = (float)num[i] / den[i];
        if (den[i] < 0)
            te.push_back(t);
        else
            tl.push_back(t);
    }

    te.push_back(0.f);
    tl.push_back(1.0);

    float tE = abs(*max_element(te.begin(), te.end()));
    float tL = abs(*min_element(tl.begin(), tl.end()));

    // If the line is inside the view-port
    if (tE <= tL)
    {
        int xs, ys, zs, xe, ye, ze;
        xs = round(l.first.X + p1p0.X * tE);
        ys = round(l.first.Y + p1p0.Y * tE);
        zs = round(l.first.Z + p1p0.Z * tE);
        xe = round(l.first.X + p1p0.X * tL);
        ye = round(l.first.Y + p1p0.Y * tL);
        ze = round(l.first.Z + p1p0.Z * tL);

        Point p1(xs, ys, zs), p2(xe, ye, ze);
        transformedLines.push_back({p1, p2});
    }
    return;
}

// Perform the clipping
void clip()
{
    initParams();
    for (auto l : orgLines)
        CyrusBeck(l);
}

void keyboard(unsigned char key, int xi, int yi)
{
    if (key == 'o' || key == 'O')
    {
        tFlag = true;
        glutTimerFunc(0, timer, 0);
    }
    else if (key == 'p' || key == 'P')
        tFlag = false;
    else if (key == 'C' || key == 'c')
    {
        flag = flag ^ 1;
        glutPostRedisplay();
    }
}

void init()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(600, 100);
    glutCreateWindow("3D Clipping");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

// Draw the bounding box
void cube()
{
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3i(XMin, YMin, ZMin);
    glVertex3i(XMax, YMin, ZMin);

    glVertex3i(XMin, YMin, ZMin);
    glVertex3i(XMin, YMax, ZMin);

    glVertex3i(XMin, YMin, ZMin);
    glVertex3i(XMin, YMin, ZMax);

    glVertex3i(XMax, YMin, ZMin);
    glVertex3i(XMax, YMax, ZMin);

    glVertex3i(XMax, YMin, ZMin);
    glVertex3i(XMax, YMin, ZMax);

    glVertex3i(XMin, YMax, ZMin);
    glVertex3i(XMax, YMax, ZMin);

    glVertex3i(XMin, YMax, ZMin);
    glVertex3i(XMin, YMax, ZMax);

    glVertex3i(XMin, YMin, ZMax);
    glVertex3i(XMax, YMin, ZMax);

    glVertex3i(XMin, YMin, ZMax);
    glVertex3i(XMin, YMax, ZMax);

    glVertex3i(XMax, YMax, ZMin);
    glVertex3i(XMax, YMax, ZMax);

    glVertex3i(XMin, YMax, ZMax);
    glVertex3i(XMax, YMax, ZMax);

    glVertex3i(XMax, YMin, ZMax);
    glVertex3i(XMax, YMax, ZMax);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, -200, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(200, 200, 200, 0, 0, 0, 0, 0, 1);
    glRotated(ang, 0, 0, 1);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    if (flag)
    {
        for (auto l : orgLines)
        {
            glVertex3i(l.first.X, l.first.Y, l.first.Z);
            glVertex3i(l.second.X, l.second.Y, l.second.Z);
        }
    }
    else
    {
        for (auto l : transformedLines)
        {
            glVertex3i(l.first.X, l.first.Y, l.first.Z);
            glVertex3i(l.second.X, l.second.Y, l.second.Z);
        }
    }
    glEnd();

    cube();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    int n;
    cout << "Enter number of lines: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int xs, ys, zs, xe, ye, ze;
        cout << "\nLine " << i + 1 << ":\n";
        cout << "Enter Start Point:\n";
        cout << "\tx: ";
        cin >> xs;
        cout << "\ty: ";
        cin >> ys;
        cout << "\tz: ";
        cin >> zs;

        cout << "Enter End Point:\n";
        cout << "\tx: ";
        cin >> xe;
        cout << "\ty: ";
        cin >> ye;
        cout << "\tz: ";
        cin >> ze;

        Point p1(xs, ys, zs), p2(xe, ye, ze);
        orgLines.push_back({p1, p2});
    }

    cout << "\nEnter Clipping Window\n";
    cout << "\tX Min: ";
    cin >> XMin;
    cout << "\tY Min: ";
    cin >> YMin;
    cout << "\tZ Min: ";
    cin >> ZMin;
    cout << "\tX Max: ";
    cin >> XMax;
    cout << "\tY Max: ";
    cin >> YMax;
    cout << "\tX Max: ";
    cin >> ZMax;

    clip();

    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}