# Computer Graphics

This directory contains all the relevant lab programs from the course Computer Graphics.

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

| S.No. | Name                                                                  | Description                                                        |
| ----- | --------------------------------------------------------------------- | ------------------------------------------------------------------ |
| 1     | [Introduction](./programs/01-Intro.cpp)                               | Generates a simple triangle                                        |
| 2     | [DDA](./programs/02-LineUsingDDA.cpp)                                 | Line generation usind DDA                                          |
| 3     | [Bresenham's Algorithm](./programs/03-Bresenham.cpp)                  | Line generation using Bresenham's Algorithm                        |
| 4     | [Dotted Line Generation](./programs/04-DashedLine.cpp)                | Dotted line generation using Bresenham's Algorithm                 |
| 5     | [Circle Generation: Parametric](./programs/05-CircleParametric.cpp)   | Circle generation using the paramteric representation of a circle  |
| 6     | [Circle Generation: Polynomial](./programs/06-CirclePolynomial.cpp)   | Circle generation using the polynomial representation of a circle  |
| 7     | [Circle Generation: Breshenham](./programs/07-CircleBreshenham.cpp)   | Circle generation using Breshenham's algorithm                     |
| 8     | [Circle Generation: Midpoint](./programs/08-CircleMidpoint.cpp)       | Circle generation using the midpoint analysis technique            |
| 9     | [Ellipse Generation: Parametric](./programs/09-EllipseParametric.cpp) | Ellopse generation using the paramteric representation of a circle |
| 10    | [Ellipse Generation: Polynomial](./programs/10-EllipsePolynomial.cpp) | Ellipse generation using the polynomial representation of a circle |
| 11    | [Ellipse Generation: Midpoint](./programs/11-EllipseMidpoint.cpp)     | Ellipse generation using the midpoint analysis technique           |
