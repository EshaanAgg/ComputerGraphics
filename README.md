# Computer Graphics

This directory contains all the relevant lab programs from the course Computer Graphics. This is meant to serve an a beginner's guide to OpenGL in C++ and implement the standard Graphic processing and rendering algorithms. You can find the screenshots of running all the binaries in the [images](./images/) directory.

### About the repository structure

All the source code files are located in the `programs` directory, and the root level `binaries` directory is for the complied binaries generated from the source code.

To compile a source code file, use the following command:

```bash
g++ programs/FileName.cpp -o binaries/FileName -lglut -lGLU -lGL
```

This will create a file called `FileName` in the `binaries` directory. You can execute the same by executing the following:

```bash
./binaries/FileName
```

For the purposes of this repository, I would not be commiting the `binaries` folder.

### Compiling all the binaries

You can compile all the binaries in one go by using the shell script.

```bash
chmod +x compile.sh
./compile.sh
```

### Programs

| S.No. | Name                                                                                    | Description                                                                                                                                       |
| ----- | --------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1     | [Introduction](./programs/01-Intro.cpp)                                                 | Generates a simple triangle                                                                                                                       |
| 2     | [DDA](./programs/02-LineUsingDDA.cpp)                                                   | Line generation usind DDA                                                                                                                         |
| 3     | [Bresenham's Algorithm](./programs/03-Bresenham.cpp)                                    | Line generation using Bresenham's Algorithm                                                                                                       |
| 4     | [Dotted Line Generation](./programs/04-DashedLine.cpp)                                  | Dotted line generation using Bresenham's Algorithm                                                                                                |
| 5     | [Circle Generation: Parametric](./programs/05-CircleParametric.cpp)                     | Circle generation using the paramteric representation of a circle                                                                                 |
| 6     | [Circle Generation: Polynomial](./programs/06-CirclePolynomial.cpp)                     | Circle generation using the polynomial representation of a circle                                                                                 |
| 7     | [Circle Generation: Breshenham](./programs/07-CircleBreshenham.cpp)                     | Circle generation using Breshenham's algorithm                                                                                                    |
| 8     | [Circle Generation: Midpoint](./programs/08-CircleMidpoint.cpp)                         | Circle generation using the midpoint analysis technique                                                                                           |
| 9     | [Ellipse Generation: Parametric](./programs/09-EllipseParametric.cpp)                   | Ellopse generation using the paramteric representation of a circle                                                                                |
| 10    | [Ellipse Generation: Polynomial](./programs/10-EllipsePolynomial.cpp)                   | Ellipse generation using the polynomial representation of a circle                                                                                |
| 11    | [Ellipse Generation: Midpoint](./programs/11-EllipseMidpoint.cpp)                       | Ellipse generation using the midpoint analysis technique                                                                                          |
| 12    | [Scanline Polygon Filling](./programs/12-ScanlinePolygon.cpp)                           | Filling colour in a polygon based on the scanline algorithm                                                                                       |
| 13    | [Floodfill Algorithm](./programs/13-Floodfill.cpp)                                      | Implement the floodfill algorithm                                                                                                                 |
| 14    | [Boundary Fill Algorithm](./programs/14-BoundaryFill.cpp)                               | Implement the boundary fill algorithm                                                                                                             |
| 15    | [Simple Geometric Transformations](./programs/15-SimpleTransformations.cpp)             | Implement translation, scaling, rotation, reflection and shearing algorithms for a triangle                                                       |
| 16    | [Reflection about Line](./programs/16-ReflectAboutLine.cpp)                             | Implement reflection of a trinagle about a line using simple geometric transformations                                                            |
| 17    | [Scaling and Rotation about a Point](./programs/17-ScaleAndRotateAboutPoint%20copy.cpp) | Implement rotation and scaling of a trinagle about a point using simple geometric transformations                                                 |
| 18    | [Window Viewport Transformation](./programs/18-WindowViewportTransformation.cpp)        | Implement window and viewport transformation algorithm, and use the inbuilt OpenGL functions to demonstrate the same on a house.                  |
| 19    | [3D Simple Transformations](./programs/19-3DTransformations.cpp)                        | Implement translation, scaling, rotation, reflection and shearing algorithms in 3D coordinates                                                    |
| 20    | [3D Composite Transformations](./programs/20-3DReflectAboutLine.cpp)                    | Rotate a cube about an arbitary line in the 3D coordinate system                                                                                  |
| 21    | [3D Composite Transformations 2](./programs/21-ReflectAboutLineParallelToXAxis.cpp)     | Rotate a cube about a line parallel to the X axis in the 3D coordinate system                                                                     |
| 22    | [Perspective Projection](./programs/22-PerspectiveProjection.cpp)                       | Project a cube onto a 2D plane using perspective projection                                                                                       |
| 23    | [Parallel Projection](./programs/22-PerspectiveProjection.cpp)                          | Project a cube onto a 2D plane using parallel projection                                                                                          |
| 24    | [Cohen Sutherland Clipping](./programs/24-CohenSutherland.cpp)                          | Demonstrate the Cohen Sutherland 2D Clipping algorithm. After entering the coordinates, press 'C' on keyboard to perform clipping.                |
| 25    | [Cyrus Beck Clipping](./programs/25-CyrusBeck.cpp)                                      | Demonstrate Cryus Beck 2D Clipping algorithm for a rectangular window. After entering the coordinates, press 'C' on keyboard to perform clipping. |
| 26    | [Liang Barsky Clipping](./programs/26-LiangBarsky.cpp)                                  | Demonstrate Liang Barsky Clipping algorithm for a rectangular window. After entering the coordinates, press 'C' on keyboard to perform clipping.  |
| 27    | [Polygon Clipping](./programs/27-PolygonClipping.cpp)                                   | Demonstrate Polygon Clipping algorithm for a quadilateral. After entering the coordinates, press 'C' on keyboard to perform clipping.             |
