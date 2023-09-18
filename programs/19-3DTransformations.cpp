#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;

// This program is for performing a transformation on the triangle
// 1 -> Translation
// 2 -> Rotation (About Z axis)
// 3 -> Scaling
// 4 -> Shearing (About X axis)
// 5 -> Reflection

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

    void print()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << val[i][j] << " ";
            cout << "\n";
        }
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

    Matrix<T> identity(int N)
    {
        Matrix<T> ans(N);
        for (int i = 0; i < N; i++)
            ans.val[i][i] = 1;
        return ans;
    }
};

namespace Geometry
{
    vector<vector<double>> points = {{40, 40, -50}, {90, 40, -50}, {90, 90, -50}, {40, 90, -50}, {30, 30, 0}, {80, 30, 0}, {80, 80, 0}, {30, 80, 0}};
    vector<vector<double>> colors = {{0.7, 0.4, 0.7}, {0.2, 0.5, 0.3}, {0.2, 0.4, 0.7}, {0.5, 0.4, 0.3}, {0.5, 0.7, 0.2}, {0.2, 0.3, 0.4}};
    vector<vector<double>> pointsTransformed(points.size(), vector<double>(3));

    void transform()
    {
        Matrix<double> mat(4);

        cout << "Enter the operator you want to perform:\n";
        cout << "1: Translation, 2: Rotation, 3: Scaling, 4: Shearing, 5: Reflection\n";
        int type;
        cin >> type;

        if (type == 1)
        {
            // Translation
            cout << "Enter Translation factors in X, Y and Z (tx,ty, tz): ";
            double tx, ty, tz;
            cin >> tx >> ty >> tz;
            mat.val = {
                {1, 0, 0, tx},
                {0, 1, 0, ty},
                {0, 0, 1, tz},
                {0, 0, 0, 1}};
        }
        else if (type == 2)
        {
            // Rotation
            double pi = 2 * acos(0);
            cout << "Enter angle theta for rotation (in degrees): ";
            double theta;
            cin >> theta;
            theta *= pi / 180;
            mat.val = {
                {cos(theta), -sin(theta), 0, 0},
                {sin(theta), cos(theta), 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}};
        }
        else if (type == 3)
        {
            // Scaling
            cout << "Enter the scale factors (sx, sy, sz): ";
            double sx, sy, sz;
            cin >> sx >> sy >> sz;
            mat.val = {
                {sx, 0, 0, 0},
                {0, sy, 0, 0},
                {0, 0, sz, 0},
                {0, 0, 0, 1}};
        }
        else if (type == 4)
        {
            // Shearing
            cout << "Enter shearing factors about X axis (sxy,sxz): ";
            double sxy, sxz;
            cin >> sxy >> sxz;
            mat.val = {
                {1, 0, 0, 0},
                {sxy, 1, 0, 0},
                {sxz, 0, 1, 0},
                {0, 0, 0, 1}};
        }
        else
        {
            // Reflection about planes
            cout << "Enter 1 for reflection about XY plane, 2 for reflection about YZ plane and 3 for reflection about XZ plane.";
            int t;
            cin >> t;
            if (t == 1)
                mat.val = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, -1, 0}, {0, 0, 0, 1}};
            else if (t == 2)
                mat.val = {{-1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
            else
                mat.val = {{1, 0, 0, 0}, {0, -1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
        }

        for (int i = 0; i < points.size(); i++)
        {
            vector<double> col = {points[i][0], points[i][1], points[i][2], 1};
            auto row = mat.multiplyColumn(col);
            pointsTransformed[i][0] = row[0];
            pointsTransformed[i][1] = row[1];
            pointsTransformed[i][2] = row[2];
        }
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
        display(points);
    }

    void displayTransformed()
    {
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
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutCreateWindow("Original");
    glOrtho(-50, 400.0, -50.0, 400.0, -50.0, 400.0);
    glutDisplayFunc(displayOriginal);

    glutCreateWindow("Transformed");
    glOrtho(-50, 400.0, -50.0, 400.0, -50.0, 400.0);
    glutDisplayFunc(displayTransformed);

    glutMainLoop();
}
