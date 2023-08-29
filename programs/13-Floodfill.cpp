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

void floodFill(GLint x, GLint y, Color oldColor, Color newColor)
{
    Color color;
    color = getPixelColor(x, y);

    if (equals(color, oldColor))
    {
        setPixelColor(x, y, newColor);
        floodFill(x + 1, y, oldColor, newColor);
        floodFill(x, y + 1, oldColor, newColor);
        floodFill(x - 1, y, oldColor, newColor);
        floodFill(x, y - 1, oldColor, newColor);
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glVertex2f(100, 100);
    glVertex2f(100, 300);
    glVertex2f(300, 300);
    glVertex2f(300, 100);
    glEnd();

    glFlush();

    // We want to colour the square red.
    Color newColor = {1.0f, 0.0f, 0.0f};
    // The square is currently coloured black.
    Color oldColor = {0.0f, 0.0f, 0.0f};

    floodFill(X, Y, oldColor, newColor);
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
    cout << "Enter the X and Y to start floodfill.\n";
    cin >> X >> Y;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Floodfill Algorithm");

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}