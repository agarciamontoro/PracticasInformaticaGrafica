Computer Graphics assignments
=============================

Computer Graphics project, built entirely with OpenGL and C++.

## Structure

The project is structured in consecutive assignments, one of each is based in the previous work.
This repo contains:

* **Assignment 1 - PLY model visualization**: Model visualization of PLY files.
* **Assignment 2 - Poligonal models**: Model generation, surfaces of revolution.
* **Assignment 3 - Hierarchical models**: Hierarchical model generation with several degrees of freedom.
* **Assignment 4 - Illumination**: Illumination control in a more complex scene.

## Installation

The libraries freeglut and libjpeg (in its development version) are needed in the compilation process. These libraries are available in the majority of Linux distributions. For compiling and/or running with the default settings, execute the following order:

    make

Once the project is compiled, run it with the following order:

    ./bin/prac <PLY_file> <PLY_revolution> <face_num>

Where *\<PLY_file\>* is the path to the PLY file loaded by assignment 1 and *\<PLY_revolution\>* is the path to the PLY file loaded by assignment 2 to generate the surface of revolution with *\<face_num\>* number of faces.

### Keys

* F1: Shows first assignment.
* F2: Shows second assignment.
* F3: Shows third assignment.
* F4: Shows fourth assignment (default).
* 1: The model is rendered in WIRE mode.
* 2: The model is rendered in SOLID mode.
* 3: The model is rendered in CHESS mode (default mode).
* 4: The model is rendered in POINT mode.
* F: Switches the visualization of the faces normals.
* V: Switches the visualization of the vertices normals.
* Q: Quits the program.

Furthermore, in the third assignment (F3), the following keys are used to manipulate the model:

* Z/z: First degree of freedom control.
* X/x: Second degree of freedom control.
* C/c: Third degree of freedom control.
* B/b: Fourth degree of freedom automatic control.

In the fourth assignment (F4), the illumination is controlled with:

* A/Z: Changes position of white light in the horizonal plane.
* X/C: Changes position of white light in the vertical plane.

## Screenshots

Assignment 1 - Beethoven PLY model in CHESS mode.

![Beethoven](https://cloud.githubusercontent.com/assets/3924815/5709707/60023f28-9a9c-11e4-866d-be10715fa5d6.png)

Assignment 1 - Car PLY model in CHESS mode.

![Car](https://cloud.githubusercontent.com/assets/3924815/5709708/6006d61e-9a9c-11e4-8630-ec637b8f5689.png)

Assignment 3 - Hierarchical model of a Dalek generated from scratch.

![Dalek](https://cloud.githubusercontent.com/assets/3924815/5709861/871ca930-9a9d-11e4-8c0f-6813928e04c7.png)
[EXTERMINATE, EXTERMINAAAAAAAAAAAAAAAAAATE!](http://en.wikipedia.org/wiki/Dalek)

Assignment 2 - Surface of revolution coloured according to the vertices normals.

![Inception](https://cloud.githubusercontent.com/assets/3924815/5709710/604d2998-9a9c-11e4-807d-593ed9681b98.png)

![Pawn](https://cloud.githubusercontent.com/assets/3924815/5709711/60508926-9a9c-11e4-87b2-bc552060f34b.png)

Assignment 4 - Scene illumination.

![Illumination](https://cloud.githubusercontent.com/assets/3924815/7338716/3d485070-ec55-11e4-922c-be6138162b95.png)


=============================
Computer Science and Mathematics Degree. University of Granada.
