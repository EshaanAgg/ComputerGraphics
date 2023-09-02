#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

#define MAX_HEIGHT 800
#define MAX_WIDTH 600
#define MAX_VERTICES 1000 // The count of maximum number of points that can be covered in one scanline

// Start from lower left corner
typedef struct EdgeBucket
{
    int YMax;    // Max y-coordinate of edge
    float XYmin; // X-coordinate of lowest edge point
    float slopeInverse;
} EdgeBucket;

typedef struct EdgeTableTuple
{
    // The edge table (ET) with edges entries sorted in increasing y and x of the lower end
    int countEdgeBucket; // No. of edgebuckets
    EdgeBucket buckets[MAX_VERTICES];
} EdgeTableTuple;

EdgeTableTuple EdgeTable[MAX_HEIGHT], ActiveEdgeTuple;

// Intialize the edge table by setting the count of buckets in each tuple as 0
void initEdgeTable()
{
    for (int i = 0; i < MAX_HEIGHT; i++)
        EdgeTable[i].countEdgeBucket = 0;
    ActiveEdgeTuple.countEdgeBucket = 0;
}

/* Function to sort an array using insertion sort*/
void insertionSort(EdgeTableTuple *ett)
{
    int i, j;
    EdgeBucket temp;

    for (i = 1; i < ett->countEdgeBucket; i++)
    {
        temp.YMax = ett->buckets[i].YMax;
        temp.XYmin = ett->buckets[i].XYmin;
        temp.slopeInverse = ett->buckets[i].slopeInverse;
        j = i - 1;

        while ((temp.XYmin < ett->buckets[j].XYmin) && (j >= 0))
        {
            ett->buckets[j + 1].YMax = ett->buckets[j].YMax;
            ett->buckets[j + 1].XYmin = ett->buckets[j].XYmin;
            ett->buckets[j + 1].slopeInverse = ett->buckets[j].slopeInverse;
            j = j - 1;
        }
        ett->buckets[j + 1].YMax = temp.YMax;
        ett->buckets[j + 1].XYmin = temp.XYmin;
        ett->buckets[j + 1].slopeInverse = temp.slopeInverse;
    }
}

void storeEdgeInTuple(EdgeTableTuple *receiver, int ym, int xm, float slopInv)
{
    int currLen = receiver->countEdgeBucket;
    (receiver->buckets[currLen]).YMax = ym;
    (receiver->buckets[currLen]).XYmin = (float)xm;
    (receiver->buckets[currLen]).slopeInverse = slopInv;

    // Sort the buckets
    insertionSort(receiver);

    (receiver->countEdgeBucket)++;
}

void storeEdgeInTable(int x1, int y1, int x2, int y2)
{
    float m, minv;
    int ymaxTS, xwithyminTS, scanline; // ts stands for to store

    if (x2 == x1)
        minv = 0.000000;
    else
    {
        m = ((float)(y2 - y1)) / ((float)(x2 - x1));

        // Horizontal lines are not stored in edge table
        if (y2 == y1)
            return;

        minv = (float)1.0 / m;
    }

    if (y1 > y2)
    {
        scanline = y2;
        ymaxTS = y1;
        xwithyminTS = x2;
    }
    else
    {
        scanline = y1;
        ymaxTS = y2;
        xwithyminTS = x1;
    }

    // The assignment part is done. Call the helper function to store the same
    storeEdgeInTuple(&EdgeTable[scanline], ymaxTS, xwithyminTS, minv);
}

void removeEdgeByYmax(EdgeTableTuple *Tup, int yy)
{
    int i, j;
    for (i = 0; i < Tup->countEdgeBucket; i++)
    {
        if (Tup->buckets[i].YMax == yy)
        {
            for (j = i; j < Tup->countEdgeBucket - 1; j++)
            {
                Tup->buckets[j].YMax = Tup->buckets[j + 1].YMax;
                Tup->buckets[j].XYmin = Tup->buckets[j + 1].XYmin;
                Tup->buckets[j].slopeInverse = Tup->buckets[j + 1].slopeInverse;
            }
            Tup->countEdgeBucket--;
            i--;
        }
    }
}

void updateXBySlopeInverse(EdgeTableTuple *Tup)
{
    for (int i = 0; i < Tup->countEdgeBucket; i++)
        (Tup->buckets[i]).XYmin = (Tup->buckets[i]).XYmin + (Tup->buckets[i]).slopeInverse;
}

void scanlineFill()
{
    /*
    Follow the following rules:
        1. Horizontal edges: Do not include in edge table
        2. Horizontal edges: Drawn either on the bottom or on the top.
        3. Vertices: If local max or min, then count twice, else count once.
        4. Either vertices at local minima or at local maxima are drawn.
    */

    int i, j, x1, ymax1, x2, ymax2, FillFlag = 0, coordCount;

    for (i = 0; i < MAX_HEIGHT; i++)
    {
        // 1. Move from ET bucket y to the AET those edges whose ymin = y (entering edges)
        for (j = 0; j < EdgeTable[i].countEdgeBucket; j++)
        {
            storeEdgeInTuple(&ActiveEdgeTuple, EdgeTable[i].buckets[j].YMax, EdgeTable[i].buckets[j].XYmin,
                             EdgeTable[i].buckets[j].slopeInverse);
        }

        // 2. Remove from AET those edges for which y=YMax (not involved in next scan line)
        removeEdgeByYmax(&ActiveEdgeTuple, i);
        insertionSort(&ActiveEdgeTuple);

        // 3. Fill lines on scan line y by using pairs of x-coords from AET
        j = 0;
        FillFlag = 0;
        coordCount = 0;
        x1 = 0;
        x2 = 0;
        ymax1 = 0;
        ymax2 = 0;

        while (j < ActiveEdgeTuple.countEdgeBucket)
        {
            if (coordCount % 2 == 0)
            {
                x1 = (int)(ActiveEdgeTuple.buckets[j].XYmin);
                ymax1 = ActiveEdgeTuple.buckets[j].YMax;
                if (x1 == x2)
                {
                    /* Three cases can arrive-
                        1. Lines are towards top of the intersection
                        2. Lines are towards bottom
                        3. One line is towards top and other is towards bottom
                    */
                    if (((x1 == ymax1) && (x2 != ymax2)) || ((x1 != ymax1) && (x2 == ymax2)))
                    {
                        x2 = x1;
                        ymax2 = ymax1;
                    }
                    else
                        coordCount++;
                }
                else
                    coordCount++;
            }
            else
            {
                x2 = (int)ActiveEdgeTuple.buckets[j].XYmin;
                ymax2 = ActiveEdgeTuple.buckets[j].YMax;

                FillFlag = 0;

                // Checking for intersection
                if (x1 == x2)
                {
                    /*
                    Three cases can arrive-
                        1. lines are towards top of the intersection
                        2. lines are towards bottom
                        3. one line is towards top and other is towards bottom
                    */
                    if (((x1 == ymax1) && (x2 != ymax2)) || ((x1 != ymax1) && (x2 == ymax2)))
                    {
                        x1 = x2;
                        ymax1 = ymax2;
                    }
                    else
                    {
                        coordCount++;
                        FillFlag = 1;
                    }
                }
                else
                {
                    coordCount++;
                    FillFlag = 1;
                }

                if (FillFlag)
                {
                    // Drawing actual line
                    glColor3f(0.0f, 0.7f, 0.0f);
                    glBegin(GL_LINES);
                    glVertex2i(x1, i);
                    glVertex2i(x2, i);
                    glEnd();
                    glFlush();
                }
            }

            j++;
        }

        updateXBySlopeInverse(&ActiveEdgeTuple);
    }
}

void myInit(void)
{

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, MAX_HEIGHT, 0, MAX_WIDTH);
    glClear(GL_COLOR_BUFFER_BIT);
}

void takeInput()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    int len, x1, y1, x2, y2, count = 0;
    cout << "Enter the number of vertices: ";
    cin >> len;
    cout << "Enter the vertices: \n";

    while (len--)
    {
        count++;
        if (count > 2)
        {
            x1 = x2;
            y1 = y2;
            count = 2;
        }

        if (count == 1)
            cin >> x1 >> y1;
        else
        {
            cin >> x2 >> y2;
            glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
            glEnd();
            storeEdgeInTable(x1, y1, x2, y2);
            glFlush();
        }
    }
}

void drawPolygon(void)
{
    initEdgeTable();
    takeInput();
    scanlineFill();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(MAX_HEIGHT, MAX_WIDTH);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Scanline Fill Algorithm");
    myInit();
    glutDisplayFunc(drawPolygon);
    glutMainLoop();
    return 0;
}
