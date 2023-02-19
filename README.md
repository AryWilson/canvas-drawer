# canvas-drawer

Implements a simple drawing api

[Alt text](https://github.com/AryWilson/canvas-drawer/tree/main/images/triangle.png?raw=true)

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
canvas-drawer $ mkdir build
canvas-drawer $ cd build
canvas-drawer/build $ cmake -G "Visual Studio 16 2019" ..
canvas-drawer/build $ start Draw-2D.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
canvas-drawer/build $ ../bin/Debug/draw_test
canvas-drawer/build $ ../bin/Debug/draw_art
```

*macOS*

Open terminal to the directory containing this repository.

```
canvas-drawer $ mkdir build
canvas-drawer $ cd build
canvas-drawer/build $ cmake ..
canvas-drawer/build $ make
```

To run each program from build, you would type

```
canvas-drawer/build $ ../bin/draw_test
canvas-drawer/build $ ../bin/draw_art
```

## Supported primitives

This project supports UNDEFINED, POINTS, LINES, and TRIANGLES as primitives accepted by the begin method for drawing by indicating each vertex.

## Results
[Alt text](https://github.com/AryWilson/canvas-drawer/tree/main/images/honey3.png?raw=true)
[Alt text](https://github.com/AryWilson/canvas-drawer/tree/main/images/save.png?raw=true)
[Alt text](https://github.com/AryWilson/canvas-drawer/tree/main/images/stars1.png?raw=true)
