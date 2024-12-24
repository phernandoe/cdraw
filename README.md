# CDRAW
Generate a grid based on user input.

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
- [ ] `vertex` folder doesn't make sense
- [ ] better namespacing for vao and vbo functions
- [ ] optional memory profiler
- [ ] condense the `vendor` folder

#### References
- https://docs.gl
- IO -> https://www.glfw.org/docs/latest/group__input.html
- https://github.com/erkkah/tigr for API inspiration
- https://www.raylib.com/cheatsheet/cheatsheet.html for API inspiration
