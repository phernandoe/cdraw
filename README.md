# CDRAW
The goal for this project is to create a C library where you can
provide a list of points and color as input, get drawing as output.

## Building the project
Requirements: 
- `cmake` (on Mac, run `brew install cmake`)
1. Run `make all`.
2. Run `make run`.

### Development
- All your changes should be in the `src` directory. 
- You should only need to run `make all` once to build GLFW and GLEW. 
- To build the `src`, run `make src`.
- Running `make run` will also build `src` and execute the resulting file.

### TODO
#### Developer Experience
- [ ] `vertex` folder doesn't make sense
- [ ] better namespacing for vao and vbo functions
- [ ] optional memory profiler

#### Features
- [ ] error handler

- [ ] API to create shapes
- [ ] line
- [ ] square
- [ ] triangle
- [ ] circle
- [ ] curved line

- [ ] API to add color
- [ ] fill color
- [ ] stroke coor

