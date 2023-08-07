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

For the purposes of this repository, I would not be commiting the `binaries` folder. However, you can compile the binaries you like by using the above methodology.

### Programs

| S.No. | Name                                                   | Description                                        |
| ----- | ------------------------------------------------------ | -------------------------------------------------- |
| 1     | [Introduction](./programs/01-Intro.cpp)                | Generates a simple triangle                        |
| 2     | [DDA](./programs/02-LineUsingDDA.cpp)                  | Line generation usind DDA                          |
| 3     | [Bresenham's Algorithm](./programs/03-Bresenham.cpp)   | Line generation using Bresenham's Algorithm        |
| 4     | [Dotted Line Generation](./programs/04-DashedLine.cpp) | Dotted line generation using Bresenham's Algorithm |
