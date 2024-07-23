#!/bin/bash

# If the glfw library hasn't been built
if [ ! -f "vendor/glfw-3.3.8/src/libglfw3.a" ]
then
	cd vendor/glfw-3.3.8
	cmake .
	make
	cd ../../
fi

gcc \
-g -Wall \
-Ivendor/glfw-3.3.8/include -Ivendor/glew-2.2.0 -Ivendor \
vendor/glfw-3.3.8/src/libglfw3.a vendor/glew-2.2.0/lib/libGLEW.a src/main.c \
-framework Cocoa -framework OpenGL -framework IOKit

./a.out
