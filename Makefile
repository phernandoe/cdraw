CC=gcc
CFLAGS=-g -Wall

GLEW=vendor/glew-2.2.0
GLFW=vendor/glfw-3.3.8

MAIN=src/main.c
LOG=src/log/*.c
UTILS=src/util/*.c
VERTEX=src/vertex/*.c

BINS=build/glew/lib64/libGLEW.a build/glfw/src/libglfw3.a
VENDOR_INCLUDES=-Ivendor/glfw-3.3.8/include -Ibuild/glew/include

# TARGET=-framework Cocoa -framework OpenGL -framework IOKit

TARGET=-lGLEW -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm

UNAME_S := $(shell unane -s)

all: glfw glew build-src

run: build-src
	./a.out

build-src: $(MAIN)
	$(CC) $(CFLAGS) $(VENDOR_INCLUDES) $(MAIN) $(UTILS) $(VERTEX) $(LOG) $(BINS) $(TARGET)

glfw: $(GLFW)
	cmake -S $(GLFW) -B build/glfw && cmake --build build/glfw

glew: $(GLEW)
	make -C $(GLEW)/auto && make -C $(GLEW) all && make -C $(GLEW) install GLEW_DEST=./../../build/glew && make -C $(GLEW) clean

clean:
	rm -dr *.o *.out *.dSYM build/ && cmake -U * $(GLFW)/CMakeCache.txt && make -C $(GLEW) clean

