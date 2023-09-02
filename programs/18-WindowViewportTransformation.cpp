#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

const int XWMin = 0, XWMax = 14, YWMin = 0, YWMax = 14;
int XVMax, XVMin, YVMax, YVMin;

void DRAW_HOUSE()
{
    glClearColor(0.0, 1.0, 1.0, 0.25);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2i(0, 0);
    glVertex2i(10, 0);
    glVertex2i(10, 10);
    glVertex2i(0, 10);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(4, 0);
    glVertex2i(4, 3);
    glVertex2i(6, 3);
    glVertex2i(6, 0);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(1, 5);
    glVertex2i(1, 8);
    glVertex2i(3, 8);
    glVertex2i(3, 5);

    glVertex2i(7, 5);
    glVertex2i(7, 8);
    glVertex2i(9, 8);
    glVertex2i(9, 5);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(0, 10);
    glVertex2i(5, 13);
    glVertex2i(10, 10);
    glEnd();

    glFlush();
}

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
    vector<pair<double, double>> points(1);
    vector<pair<double, double>> pointsTransformed(1);

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

        double sx = (double)(XVMax - XVMin) / (double)(XWMax - XWMin);
        double sy = (double)(YVMax - YVMin) / (double)(YWMax - YWMin);

        translate(-XWMin, -YWMin);
        scale(sx, sy);
        translate(XVMin, YVMin);

        cout << "The viewport coordinates are: " << pointsTransformed[0].first << " " << pointsTransformed[0].second << "\n";
    }
}

using Geometry::points;
using Geometry::transform;

int main(int argc, char **argv)
{

    cout << "Enter the window coordinates. \n";
    cin >> points[0].first >> points[0].second;

    cout << "Enter the minimum and maximum X cordinates of viewport. \n";
    cin >> XVMin >> XVMax;

    cout << "Enter the minimum and maximum Y cordinates of viewport. \n";
    cin >> YVMin >> YVMax;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glClearColor(1.0, 1.0, 1.0, 0);

    transform();

    glutCreateWindow("Window");
    gluOrtho2D(XWMin, XWMax, YWMin, YWMax);
    glutDisplayFunc(DRAW_HOUSE);

    glutCreateWindow("Viewport");
    gluOrtho2D(XVMin, XVMax, YVMin, YVMax);
    glutDisplayFunc(DRAW_HOUSE);

    glutMainLoop();
}
