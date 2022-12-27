CC=gcc
CFLAGS=-g -Wall

GLEW=vendor/glew-2.2.0
GLFW=vendor/glfw-3.3.8

MAIN=src/main.c

BINS=build/glew/lib/libGLEW.a build/glfw/src/libglfw3.a
# TODO: Do I need these inlcudes here?
VENDOR_INCLUDES=-Ivendor/glfw-3.3.8/include -Ibuild/glew/include -Ivendor

TARGET=-framework Cocoa -framework OpenGL -framework IOKit

all: glfw glew build-src

run: build-src
	./a.out

build-src: $(MAIN)
	$(CC) $(CFLAGS) $(VENDOR_INCLUDES) $(BINS) $(MAIN) $(TARGET)

glfw: $(GLFW)
	cmake -S vendor/glfw-3.3.8 -B build/glfw && cmake --build build/glfw
glew: $(GLEW)
	cd $(GLEW)/auto && make && cd ./.. && make all && make install GLEW_DEST=./../../build/glew

clean: 
	rm -dr *.o *.out *.dSYM build/glfw/* build/glew/*