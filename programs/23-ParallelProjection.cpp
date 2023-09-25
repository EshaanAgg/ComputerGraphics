#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

vector<vector<float>> cube(24, vector<float>(4, 0));
vector<vector<float>> cubeTransformed(24, vector<float>(4, 0));
vector<vector<float>> planeView(24, vector<float>(4, 0));

vector<vector<float>> origin(1, vector<float>(4, 0));
vector<vector<float>> originTransformed(1, vector<float>(4, 0));

// The perspective transformation matrix
vector<vector<float>> T(4, vector<float>(4, 0));

float a, b, c;    // Direction of projection
float X0, Y0, Z0; // Cordinates of reference point on the view plane
float n1, n2, n3; // Normal vector to the view plane
float d0, d1;

// Multiplies the matrix A by matrix B and stores the result in matrix C
void matrixMult(vector<vector<float>> &A, vector<vector<float>> &B, vector<vector<float>> &C)
{
    int V = B.size();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < V; j++)
        {
            float temp = 0;

            for (int k = 0; k < 4; k++)
                temp += A[i][k] * B[j][k];

            C[j][i] = temp;
        }
}

// Draw a cube one face at a time, each described by 4 vertices
void drawCube(vector<vector<float>> &P)
{
    glLineWidth(2.0);
    for (int i = 0; i < 24; i += 4)
    {
        glBegin(GL_LINE_LOOP);
        for (int j = 0; j < 4; j++)
            glVertex3f(P[i + j][0], P[i + j][1], P[i + j][2]);
        glEnd();
    }
    glLineWidth(1.0);
}

// Normalize the vertices of a tranformed cube
void normalize(vector<vector<float>> &P)
{
    for (int i = 0; i < P.size(); i++)
        for (int j = 0; j < 4; j++)
            P[i][j] = P[i][j] / P[i][3];
}

void display3D()
{
    // Init 3D display
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 4.0 / 3.0, 1, 40);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4, 6, 5, 0, 0, 0, 0, 1, 0);

    // Draw all the axes with different colours
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    // X Axis
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(10, 0, 0);
    // Y Axis
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 10, 0);
    // Z Axis
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 10);
    glEnd();

    // Draw the original and the transformed cube
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCube(cube);
    matrixMult(T, cube, cubeTransformed);
    normalize(cubeTransformed);
    glColor3f(0.5f, 0.5f, 0.5f);
    drawCube(cubeTransformed);

    glFlush();
}

void displayViewPlane()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    matrixMult(T, origin, originTransformed);
    normalize(originTransformed);

    float scale = 1;
    float t1[3], t2[3];

    t1[0] = n3;
    t1[1] = 0;
    t1[2] = -n1;
    t2[0] = -n2 * n1;
    t2[1] = n1 * n1 + n3 * n3;
    t2[2] = -n2 * n3;

    for (int i = 0; i < planeView.size(); i++)
    {
        float temp1 = 0, temp2 = 0;

        for (int j = 0; j < 3; j++)
        {
            temp1 += scale * t1[j] * (cubeTransformed[i][j] - originTransformed[0][j]);
            temp2 += scale * t2[j] * (cubeTransformed[i][j] - originTransformed[0][j]);
        }

        planeView[i][0] = temp1;
        planeView[i][1] = temp2;
    }

    for (int i = 0; i < 24; i += 4)
    {
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 0.0f, 1.0f);
        for (int j = 0; j < 4; j++)
            glVertex2f(planeView[i + j][0], planeView[i + j][1]);
        glEnd();
    }
}

int main(int argc, char **argv)
{
    // Define the 6 faces of a unit cube along the axes with an corner an origin
    cube = {{1.0, 1.0, 1.0, 1.0},
            {1.0, 1.0, 0.0, 1.0},
            {0.0, 1.0, 0.0, 1.0},
            {0.0, 1.0, 1.0, 1.0},

            {1.0, 0.0, 1.0, 1.0},
            {1.0, 0.0, 0.0, 1.0},
            {0.0, 0.0, 0.0, 1.0},
            {0.0, 0.0, 1.0, 1.0},

            {1.0, 1.0, 1.0, 1.0},
            {0.0, 1.0, 1.0, 1.0},
            {0.0, 0.0, 1.0, 1.0},
            {1.0, 0.0, 1.0, 1.0},

            {1.0, 1.0, 0.0, 1.0},
            {0.0, 1.0, 0.0, 1.0},
            {0.0, 0.0, 0.0, 1.0},
            {1.0, 0.0, 0.0, 1.0},

            {1.0, 1.0, 1.0, 1.0},
            {1.0, 0.0, 1.0, 1.0},
            {1.0, 0.0, 0.0, 1.0},
            {1.0, 1.0, 0.0, 1.0},

            {0.0, 1.0, 1.0, 1.0},
            {0.0, 0.0, 1.0, 1.0},
            {0.0, 0.0, 0.0, 1.0},
            {0.0, 1.0, 0.0, 1.0}};

    origin = {{0.0, 0.0, 0.0, 1.0}};

    cout << "Enter the direction of projection (a, b, c): ";
    cin >> a >> b >> c;
    cout << "Enter the reference point on view plane R0 (x0, y0, z0): ";
    cin >> X0 >> Y0 >> Z0;
    cout << "Enter the normal vector of view plane N (n1, n2, n3): ";
    cin >> n1 >> n2 >> n3;

    // Perform the distance calculations
    d0 = n1 * X0 + n2 * Y0 + n3 * Z0;
    d1 = n1 * a + n2 * b + n3 * c;

    // Populate the transformation matrix
    T[0][0] = d1 - a * n1;
    T[0][1] = -a * n2;
    T[0][2] = -a * n3;
    T[0][3] = a * d0;
    T[1][0] = -b * n1;
    T[1][1] = d1 - b * n2;
    T[1][2] = -b * n3;
    T[1][3] = b * d0;
    T[2][0] = -c * n1;
    T[2][1] = -c * n2;
    T[2][2] = d1 - c * n3;
    T[2][3] = c * d0;
    T[3][0] = 0;
    T[3][1] = 0;
    T[3][2] = 0;
    T[3][3] = d1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(80, 80);
    glutInitWindowSize(600, 450);
    glutCreateWindow("World State in 3D");
    glutDisplayFunc(display3D);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(450, 450);
    glutCreateWindow("View Plane");
    gluOrtho2D(-2.5, 2.5, -2.5, 2.5);
    glutDisplayFunc(displayViewPlane);

    glutMainLoop();
    return 0;
}
