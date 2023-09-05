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
    vector<pair<double, double>> points(3);
    vector<pair<double, double>> pointsTransformed(3);

    void apply(Matrix<double> mat)
    {
        for (int i = 0; i < points.size(); i++)
        {
            vector<double> col = {pointsTransformed[i].first, pointsTransformed[i].second, 1};
            auto row = mat.multiplyColumn(col);
            pointsTransformed[i].first = row[0];
            pointsTransformed[i].second = row[1];
        }
    }

    void translate(double tx, double ty)
    {
        Matrix<double> mat(3);
        mat.val = {
            {1, 0, tx},
            {0, 1, ty},
            {0, 0, 1}};
        apply(mat);
    }

    void rotate(double theta)
    {
        Matrix<double> mat(3);
        mat.val = {
            {cos(theta), -sin(theta), 0},
            {sin(theta), cos(theta), 0},
            {0, 0, 1}};
        apply(mat);
    }

    void scale(double sx, double sy)
    {
        Matrix<double> mat(3);
        mat.val = {
            {sx, 0, 0},
            {0, sy, 0},
            {0, 0, 1}};
        apply(mat);
    }

    void transform()
    {
        pointsTransformed = points;

        cout << "Enter the co-ordinates of the fixed point. \n";
        double x, y;
        cin >> x >> y;

        cout << "Enter the scaling factors in x and y. \n";
        double sx, sy;
        cin >> sx >> sy;

        cout << "Enter the angle of rotation. \n";
        double theta;
        cin >> theta;
        double pi = 2 * acos(-1);
        theta *= pi / 180;

        translate(-x, -y);
        rotate(theta);
        scale(sx, sy);
        translate(x, y);
    }

    void draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0);
        for (auto [x, y] : points)
            glVertex2f(x, y);
        glEnd();
        glFlush();
    }

    void drawTransformed()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0);
        for (auto [x, y] : pointsTransformed)
            glVertex2f(x, y);
        glEnd();
        glFlush();
    }
}

using Geometry::draw;
using Geometry::drawTransformed;
using Geometry::points;
using Geometry::transform;

int main(int argc, char **argv)
{

    cout << "Enter the co-ordinates of triangle. \n";
    cout << "(X1,Y1):";
    cin >> points[0].first >> points[0].second;
    cout << "(X2,Y2):";
    cin >> points[1].first >> points[1].second;
    cout << "(X3,Y3):";
    cin >> points[2].first >> points[2].second;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glClearColor(1.0, 1.0, 1.0, 0);

    transform();

    glutCreateWindow("Original Triangle");
    gluOrtho2D(0, 640, 0, 480);
    glutDisplayFunc(draw);

    glutCreateWindow("Transformed Triangle");
    gluOrtho2D(0, 640, 0, 480);
    glutDisplayFunc(drawTransformed);

    glutMainLoop();
}
