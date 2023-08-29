#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

int X, Y;

struct Color
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

Color getPixelColor(GLint x, GLint y)
{
    Color color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

void setPixelColor(GLint x, GLint y, Color color)
{
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

bool equals(Color a, Color b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b;
}

void boundaryFill(GLint x, GLint y, Color boundColor, Color newColor)
{
    Color color;
    color = getPixelColor(x, y);

    if (!equals(color, boundColor) && !equals(color, newColor))
    {
        setPixelColor(x, y, newColor);
        boundaryFill(x + 1, y, boundColor, newColor);
        boundaryFill(x, y + 1, boundColor, newColor);
        boundaryFill(x - 1, y, boundColor, newColor);
        boundaryFill(x, y - 1, boundColor, newColor);
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    vector<vector<int>> points = {{100, 100},
                                  {100, 300},
                                  {300, 300},
                                  {300, 100}};

    for (int i = 0; i < 4; i++)
    {
        glBegin(GL_LINES);
        glVertex2f(points[i][0], points[i][1]);
        glVertex2f(points[(i + 1) % 4][0], points[(i + 1) % 4][1]);
        glEnd();
    }

    glFlush();

    // We want to colour the square red.
    Color newColor = {1.0f, 0.0f, 0.0f};
    // The square is currently coloured black.
    Color boundColor = {0.0f, 0.0f, 0.0f};

    boundaryFill(X, Y, boundColor, newColor);
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv)
{
    cout << "Enter the X and Y to start boundary fill.\n";
    cin >> X >> Y;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Boundary Fill Algorithm");

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}