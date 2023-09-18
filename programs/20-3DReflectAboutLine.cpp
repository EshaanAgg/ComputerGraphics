#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

template <typename T>
class Matrix
{
public:
    vector<vector<T>> val;
    int n;

    Matrix<T>(int size)
    {
        n = size;
        val.resize(n);
        for (int i = 0; i < n; i++)
            val[i].resize(n);
    }

    Matrix<T> &operator=(const Matrix<T> &b)
    {
        val = b.val;
        n = b.n;
        return *this;
    }

    vector<T> multiplyColumn(const vector<T> &col)
    {
        int n = col.size();
        vector<T> row(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                row[i] += this->val[i][j] * col[j];
        return row;
    }

    Matrix<T> operator*(const Matrix<T> &b) const
    {
        Matrix<T> ans(b.n);
        for (int i = 0; i < b.n; i++)
            for (int j = 0; j < b.n; j++)
                for (int k = 0; k < b.n; k++)
                    ans.val[i][j] += this->val[i][k] * b.val[k][j];
        return ans;
    }
};

namespace Geometry
{
    vector<vector<double>> points = {{40, 40, -50}, {90, 40, -50}, {90, 90, -50}, {40, 90, -50}, {30, 30, 0}, {80, 30, 0}, {80, 80, 0}, {30, 80, 0}};
    vector<vector<double>> colors = {{0.7, 0.4, 0.7}, {0.2, 0.5, 0.3}, {0.2, 0.4, 0.7}, {0.5, 0.4, 0.3}, {0.5, 0.7, 0.2}, {0.2, 0.3, 0.4}};
    vector<vector<double>> pointsTransformed(points.size(), vector<double>(3));

    void apply(Matrix<double> mat)
    {
        for (int i = 0; i < points.size(); i++)
        {
            vector<double> col = {pointsTransformed[i][0], pointsTransformed[i][1], pointsTransformed[i][2], 1};
            auto row = mat.multiplyColumn(col);
            pointsTransformed[i][0] = row[0];
            pointsTransformed[i][1] = row[1];
            pointsTransformed[i][2] = row[2];
        }
    }

    void translate(double tx, double ty, double tz)
    {
        Matrix<double> mat(4);
        mat.val = {
            {1, 0, 0, tx},
            {0, 1, 0, ty},
            {0, 0, 1, tz},
            {0, 0, 0, 1}};
        apply(mat);
    }

    void rotateZ(double cos, double sin)
    {
        Matrix<double> mat(4);
        mat.val = {
            {cos, -sin, 0, 0},
            {sin, cos, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}};
        apply(mat);
    }

    void rotateX(double cos, double sin)
    {
        Matrix<double> mat(4);
        mat.val = {
            {1, 0, 0, 0},
            {0, cos, -sin, 0},
            {0, sin, cos, 0},
            {0, 0, 0, 1}};
        apply(mat);
    }

    void rotateY(double cos, double sin)
    {
        Matrix<double> mat(4);
        mat.val = {
            {cos, 0, -sin, 0},
            {0, 1, 0, 0},
            {sin, 0, cos, 0},
            {0, 0, 0, 1}};
        apply(mat);
    }

    void transform()
    {
        pointsTransformed = points;

        // Input the points
        cout << "Enter the coordinates of A (x1, y1, z1) and the B (x2, y2, z2) through which the line passes. \n";
        vector<double> A(3), B(3), dir(3);
        for (int i = 0; i < 3; i++)
            cin >> A[i];
        for (int i = 0; i < 3; i++)
            cin >> B[i];

        // Draw the line
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex3f(A[0], A[1], A[2]);
        glVertex3f(B[0], B[1], B[2]);
        glEnd();

        // Input the angle of rotation
        cout << "Enter the angle of rotation theta (in degrees): ";
        double theta;
        cin >> theta;
        double pi = 2 * acos(0);
        theta *= pi / 180;

        // Direction cosine calculations
        double MOD = 0;
        for (int i = 0; i < 3; i++)
        {
            dir[i] = B[i] - A[i];
            MOD += pow(dir[i], 2);
        }
        MOD = sqrt(MOD);
        for (int i = 0; i < 3; i++)
            dir[i] /= MOD;
        double d = sqrt(dir[1] * dir[1] + dir[2] * dir[2]);

        // Apply the transformations
        translate(-A[0], -A[1], -A[2]);
        if (d != 0)
            rotateX(dir[2] / d, dir[1] / d);
        rotateY(d, -dir[0]);
        rotateZ(cos(theta), sin(theta));
        rotateY(d, dir[0]);
        if (d != 0)
            rotateX(dir[2] / d, -dir[1] / d);
        translate(A[0], A[1], A[2]);
    }

    void drawAxes()
    {
        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_LINES); // Plotting X-Axis
        glVertex3f(-1000, 0, 0);
        glVertex3f(1000, 0, 0);
        glEnd();

        glBegin(GL_LINES); // Plotting Y-Axis
        glVertex3f(0, -1000, 0);
        glVertex3f(0, 1000, 0);
        glEnd();

        glBegin(GL_LINES); // Plotting Z-Axis
        glVertex3s(0, 0, -1000);
        glVertex3s(0, 0, 1000);
        glEnd();
    }

    void display(vector<vector<double>> a)
    {
        int i;
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex3f(a[0][0], a[0][1], a[0][2]);
        glVertex3f(a[1][0], a[1][1], a[1][2]);
        glVertex3f(a[2][0], a[2][1], a[2][2]);
        glVertex3f(a[3][0], a[3][1], a[3][2]);
        glEnd();

        i = 0;
        glColor3f(1.0, 0, 0);
        glBegin(GL_POLYGON);
        glVertex3f(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
        glVertex3f(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
        glVertex3f(a[5 + i][0], a[5 + i][1], a[5 + i][2]);
        glVertex3f(a[4 + i][0], a[4 + i][1], a[4 + i][2]);
        glEnd();

        glColor3f(0, 1, 0);
        glBegin(GL_POLYGON);
        glVertex3f(a[0][0], a[0][1], a[0][2]);
        glVertex3f(a[3][0], a[3][1], a[3][2]);
        glVertex3f(a[7][0], a[7][1], a[7][2]);
        glVertex3f(a[4][0], a[4][1], a[4][2]);
        glEnd();

        i = 1;
        glColor3f(0, 0, 1);
        glBegin(GL_POLYGON);
        glVertex3f(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
        glVertex3f(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
        glVertex3f(a[5 + i][0], a[5 + i][1], a[5 + i][2]);
        glVertex3f(a[4 + i][0], a[4 + i][1], a[4 + i][2]);
        glEnd();

        i = 2;
        glColor3f(1.0, 0.4, 0.1);
        glBegin(GL_POLYGON);
        glVertex3f(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
        glVertex3f(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
        glVertex3f(a[5 + i][0], a[5 + i][1], a[5 + i][2]);
        glVertex3f(a[4 + i][0], a[4 + i][1], a[4 + i][2]);
        glEnd();

        i = 4;
        glColor3f(0.4, 1.0, 0.4);
        glBegin(GL_POLYGON);
        glVertex3f(a[0 + i][0], a[0 + i][1], a[0 + i][2]);
        glVertex3f(a[1 + i][0], a[1 + i][1], a[1 + i][2]);
        glVertex3f(a[2 + i][0], a[2 + i][1], a[2 + i][2]);
        glVertex3f(a[3 + i][0], a[3 + i][1], a[3 + i][2]);
        glEnd();
    }

    void displayOriginal()
    {
        drawAxes();
        display(points);
    }

    void displayTransformed()
    {
        drawAxes();
        display(pointsTransformed);
    }
}

using Geometry::displayOriginal;
using Geometry::displayTransformed;
using Geometry::transform;

int main(int argc, char **argv)
{
    // Calculate the transformed coordinates
    transform();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(0, 0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutCreateWindow("Original");
    glOrtho(-200, 400.0, -200.0, 400.0, -200.0, 400.0);
    glutDisplayFunc(displayOriginal);

    glutCreateWindow("Transformed");
    glOrtho(-200, 400.0, -200.0, 400.0, -200.0, 400.0);
    glutDisplayFunc(displayTransformed);

    glutMainLoop();
}
