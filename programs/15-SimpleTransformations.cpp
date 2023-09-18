#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

// This program is for performing a transformation on the triangle
// 1 -> Translation
// 2 -> Rotation
// 3 -> Scaling
// 4 -> Shearing
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
        {
            for (int j = 0; j < n; j++)
            {
                row[i] += this->val[i][j] * col[j];
            }
        }
        return row;
    }

    void print()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << val[i][j] << " ";
            }
            cout << "\n";
        }
    }

    Matrix<T> operator*(const Matrix<T> &b) const
    {
        Matrix<T> ans(b.n);
        for (int i = 0; i < b.n; i++)
        {
            for (int j = 0; j < b.n; j++)
            {
                for (int k = 0; k < b.n; k++)
                {
                    ans.val[i][j] += this->val[i][k] * b.val[k][j];
                }
            }
        }
        return ans;
    }

    Matrix<T> identity(int N)
    {
        Matrix<T> ans(N);
        for (int i = 0; i < N; i++)
        {
            ans.val[i][i] = 1;
        }
        return ans;
    }
};

namespace Geometry
{
    vector<pair<double, double>> points(3);
    vector<pair<double, double>> pointsTransformed(3);

    void transform()
    {
        Matrix<double> mat(3);

        cout << "Enter the operator you want to perform:\n";
        cout << "1: Translation, 2: Rotation, 3: Scaling, 4: Shearing, 5: Reflection\n";
        int type;
        cin >> type;

        if (type == 1)
        {
            // Translation
            cout << "Enter Translation factors in X and Y (tx,ty): ";
            double tx, ty;
            cin >> tx >> ty;
            mat.val = {
                {1, 0, tx},
                {0, 1, ty},
                {0, 0, 1}};
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
                {cos(theta), -sin(theta), 0},
                {sin(theta), cos(theta), 0},
                {0, 0, 1}};
        }
        else if (type == 3)
        {
            cout << "Enter the scale factors in X and Y (sx, sy): ";
            double sx, sy;
            cin >> sx >> sy;
            mat.val = {
                {sx, 0, 0},
                {0, sy, 0},
                {0, 0, 1}};
        }
        else if (type == 4)
        {
            cout << "Enter shearing factors in X and Y (sx,sy): ";
            double shx, shy;
            cin >> shx >> shy;
            mat.val = {
                {1, shx, 0},
                {shy, 1, 0},
                {0, 0, 1}};
        }
        else
        {
            cout << "Enter 1 for reflection about X axis, and 2 for reflection about Y: ";
            int t;
            cin >> t;
            if (t == 1)
                mat.val = {{1, 0, 0}, {0, -1, 0}, {0, 0, 1}};
            else
                mat.val = {{-1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        }

        for (int i = 0; i < points.size(); i++)
        {
            vector<double> col = {points[i].first, points[i].second, 1};
            auto row = mat.multiplyColumn(col);
            pointsTransformed[i].first = row[0];
            pointsTransformed[i].second = row[1];
        }
    }

    void drawOrginial()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        for (auto [x, y] : points)
            glVertex2f(x, y);
        glEnd();
        glFlush();
    }

    void drawTransformed()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        for (auto [x, y] : pointsTransformed)
            glVertex2f(x, y);
        glEnd();
        glFlush();
    }

}

using Geometry::drawOrginial;
using Geometry::drawTransformed;
using Geometry::points;
using Geometry::transform;

int main(int argc, char **argv)
{
    cout << "Enter the co-ordinates of triangle.\n";
    cout << "(X1,Y1): ";
    cin >> points[0].first >> points[0].second;
    cout << "(X2,Y2): ";
    cin >> points[1].first >> points[1].second;
    cout << "(X3,Y3): ";
    cin >> points[2].first >> points[2].second;
    cout << "\n";

    // Calculate the transformed coordinates
    transform();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glutCreateWindow("Original Triangle");
    gluOrtho2D(-300, 300, -300, 300);
    glutDisplayFunc(drawOrginial);

    glutCreateWindow("Transformed Triangle");
    gluOrtho2D(-300, 300, -300, 300);
    glutDisplayFunc(drawTransformed);

    glutMainLoop();
}
