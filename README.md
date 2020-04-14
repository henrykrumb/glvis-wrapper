# glvis-wrapper

C++ wrapper class for [GLVis](https://github.com/GLVis/glvis) to visualize
MFEM meshes.

## Prerequisites

As this wrapper is intended to be used for MFEM applications, you need to specify
the path to MFEM in CMake settings.

## Getting Started

To use this wrapper class, you can simply copy the .cpp and .h files to your
current project's source file directory and adjust the linker settings
respectively.

If you wish to include this module as a shared library, you can go the standard
CMake-way:

```bash
mkdir -p build
cd build
cmake ..
make
```

## Example Usage

Suppose we have created both a Mesh and a GridFunction object, we can call:

```C++
GLVisWrapper viz;
viz.set_antialiasing(true);
viz.set_meshmode(MESH_ELEMENT_EDGES);
viz.set_colorbar(false);
viz.set_boundingbox(BB_COORDS);
viz.set_light(true);
viz.visualize(mesh, gridfunc, "Window Title");
```

to visualize the mesh with specified properties.

## TODO

This wrapper only implements a subset of GLVis' functionalities.
Here's an incomplete list of things still needed to be implemented:

* [] R (2D projections)
* [] j (perspective)
* [] s (cube scaling)
* [x] c (toggle color bar)
* [] C (plot caption)
* [] p/P (color palettes)
* [] t (materials/lights)
* [x] l (toggle light)
* [x] a (bounding box axes)
* [x] m (mesh state)
* [] e (elements state)
* [] S (snapshots)
* [] Ctrl+p (print to pdf)
* [] f (shading)
* [] i/I (3D subdivisions)
* [x] A (antialiasing)
* [] b (boundary in 2D scalar mode)
* [] L (log scaling)
* [] \ (light source position)
* [] \* / (zoom in, out)
* [] +/- (stretch/compress)
* [] [/] (enlarge/shrink bounding box)
* [] . (toggle spinnning)
* [] w (2D clipping)
* [] l/K (transparency)
* [] ! (texture)
