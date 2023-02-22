# CDRAW

## Building the project
### Building GFLW
Requirements: 
- `cmake`
1. Run `cmake -S vendor/glfw-3.3.8 -B build` to generate build in the root `build` directory.
2. Compile the library with `cmake --build build`.
3. The resulting `build/src/libglfw3.a` file will be the binary to link.
4. `vendor/glfw-3.3.8/include` are GLFW's dependencies.

#### TODO
[] memory profiler
[] error handler