#include <GL/gl.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

namespace Geometry
{
#define N 4   // Number of Control points
#define D 2   // number of Dimensions
#define T 100 // Number of subintervals

    // Initial values of the control points
    static GLfloat ctrlPoints[N][3] = {
        {100, 100, 0}, {200, 350, 0}, {400, 300, 0}, {480, 100, 0}};
    GLUnurbsObj *theNurb;

    int windowWidth = 1000;
    int windowHeight = 800;
    int MOVENAME = -1;
    int pickRadius = 50;

    // Display the curve by plotting a stripped line between control points
    void display2DControlPolyline()
    {
        glLineWidth(2.0);
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < N; i++)
            glVertex2i(ctrlPoints[i][0], ctrlPoints[i][1]);
        glEnd();
        glFlush();
    }

    // Display the control points
    void display2DControlPoints()
    {
        glPointSize(3.0);
        glColor3f(0.0f, 1.0f, 0.0f);

        glBegin(GL_POINTS);
        for (int i = 0; i < N; i++)
        {
            glVertex2i(ctrlPoints[i][0], ctrlPoints[i][1]);
        }
        glEnd();
        glFlush();
    }

    // Bernstein polynomials co-eficient multiplication to get the coordinates
    GLfloat bernstein(GLfloat u, int i, int n)
    {
        GLfloat choose[N] = {1, 3, 3, 1};
        GLfloat nChoosei = choose[i];
        GLfloat ui = pow(u, i);
        GLfloat oneMinusu = pow(1.0 - u, n - i);

        return (nChoosei * ui * oneMinusu);
    }

    // Perform the Bezier calculations and plot the point
    void bezier()
    {
        glLineWidth(2.0);
        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_LINE_STRIP);

        for (int uInt = 0; uInt <= T; uInt++)
        {
            GLfloat u = uInt / (GLfloat)T;

            GLfloat x = 0.0;
            GLfloat y = 0.0;

            for (int i = 0; i < N; i++)
            {
                GLfloat b = bernstein(u, i, N - 1);
                x += b * ctrlPoints[i][0];
                y += b * ctrlPoints[i][1];
            }
            glVertex2i(x, y);
        }

        glEnd();
        glFlush();
    }

    void bezierDisplay()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        display2DControlPolyline();
        display2DControlPoints();
        bezier();
        glFlush();
    }

    // Mouse function
    void mouseController(int button, int state, int xPosition, int yPosition)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            GLuint newX = xPosition;
            GLuint newY = windowHeight - yPosition;
            int choiceFound = 0;

            // Determine which control point are we trying to move and store that in `MOVENAME`
            for (int i = 0; i < N && !choiceFound; i++)
            {
                if ((abs(ctrlPoints[i][0] - newX) <= pickRadius) &&
                    (abs(ctrlPoints[i][1] - newY) <= pickRadius))
                {
                    MOVENAME = i;
                    choiceFound = 1;
                }
            }
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
            MOVENAME = -1;
        glutPostRedisplay();
    }

    // Whenever the mouse is dragging a point, refresh the screen to show the dragging
    void motionController(int xPosition, int yPosition)
    {
        if (MOVENAME > -1)
        {
            GLuint newX = xPosition;
            GLuint newY = windowHeight - yPosition;
            ctrlPoints[MOVENAME][0] = newX;
            ctrlPoints[MOVENAME][1] = newY;
            glutPostRedisplay();
        }
    }

    // Updating the viewport with respect to the height and width passed
    void reshapeController(int w, int h)
    {
        glViewport(0, 0, (GLsizei)w, (GLsizei)h);
        windowWidth = w;
        windowHeight = h;
    }

}

using namespace Geometry;

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bezier Curve");

    glutDisplayFunc(bezierDisplay);
    glutMouseFunc(mouseController);
    glutMotionFunc(motionController);
    glutReshapeFunc(reshapeController);

    glClearColor(0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
    glutMainLoop();
    return 0;
}
