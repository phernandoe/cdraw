# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.25.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.25.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/fernando/dev/cdraw/vendor/glfw-3.3.8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/fernando/dev/cdraw/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/iconify.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/iconify.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/iconify.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/iconify.dir/flags.make

tests/CMakeFiles/iconify.dir/iconify.c.o: tests/CMakeFiles/iconify.dir/flags.make
tests/CMakeFiles/iconify.dir/iconify.c.o: /Users/fernando/dev/cdraw/vendor/glfw-3.3.8/tests/iconify.c
tests/CMakeFiles/iconify.dir/iconify.c.o: tests/CMakeFiles/iconify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fernando/dev/cdraw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/iconify.dir/iconify.c.o"
	cd /Users/fernando/dev/cdraw/build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/iconify.dir/iconify.c.o -MF CMakeFiles/iconify.dir/iconify.c.o.d -o CMakeFiles/iconify.dir/iconify.c.o -c /Users/fernando/dev/cdraw/vendor/glfw-3.3.8/tests/iconify.c

tests/CMakeFiles/iconify.dir/iconify.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/iconify.c.i"
	cd /Users/fernando/dev/cdraw/build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/fernando/dev/cdraw/vendor/glfw-3.3.8/tests/iconify.c > CMakeFiles/iconify.dir/iconify.c.i

tests/CMakeFiles/iconify.dir/iconify.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/iconify.c.s"
	cd /Users/fernando/dev/cdraw/build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/fernando/dev/cdraw/vendor/glfw-3.3.8/tests/iconify.c -o CMakeFiles/iconify.dir/iconify.c.s

tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o: tests/CMakeFiles/iconify.dir/flags.make
tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o: /Users/fernando/dev/cdraw/vendor/glfw-3.3.8/deps/getopt.c
tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o: tests/CMakeFiles/iconify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fernando/dev/cdraw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o"
	cd /Users/fernando/dev/cdraw/build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o -MF CMakeFiles/iconify.dir/__/deps/getopt.c.o.d -o CMakeFiles/iconify.dir/__/deps/getopt.c.o -c /Users/fernando/dev/cdraw/vendor/glfw-3.3.8/deps/getopt.c

tests/CMakeFiles/iconify.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/__/deps/getopt.c.i"
	cd /Users/fernando/dev/cdraw/build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/fernando/dev/cdraw/vendor/glfw-3.3.8/deps/getopt.c > CMakeFiles/iconify.dir/__/deps/getopt.c.i

tests/CMakeFiles/iconify.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/__/deps/getopt.c.s"
	cd /Users/fernando/dev/cdraw/build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/fernando/dev/cdraw/vendor/glfw-3.3.8/deps/getopt.c -o CMakeFiles/iconify.dir/__/deps/getopt.c.s

tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o: tests/CMakeFiles/iconify.dir/flags.make
tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o: /Users/fernando/dev/cdraw/vendor/glfw-3.3.8/deps/glad_gl.c
tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o: tests/CMakeFiles/iconify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fernando/dev/cdraw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o"
	cd /Users/fernando/dev/cdraw/build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o -MF CMakeFiles/iconify.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/iconify.dir/__/deps/glad_gl.c.o -c /Users/fernando/dev/cdraw/vendor/glfw-3.3.8/deps/glad_gl.c

tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/__/deps/glad_gl.c.i"
	cd /Users/fernando/dev/cdraw/build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/fernando/dev/cdraw/vendor/glfw-3.3.8/deps/glad_gl.c > CMakeFiles/iconify.dir/__/deps/glad_gl.c.i

tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/__/deps/glad_gl.c.s"
	cd /Users/fernando/dev/cdraw/build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/fernando/dev/cdraw/vendor/glfw-3.3.8/deps/glad_gl.c -o CMakeFiles/iconify.dir/__/deps/glad_gl.c.s

# Object files for target iconify
iconify_OBJECTS = \
"CMakeFiles/iconify.dir/iconify.c.o" \
"CMakeFiles/iconify.dir/__/deps/getopt.c.o" \
"CMakeFiles/iconify.dir/__/deps/glad_gl.c.o"

# External object files for target iconify
iconify_EXTERNAL_OBJECTS =

tests/iconify: tests/CMakeFiles/iconify.dir/iconify.c.o
tests/iconify: tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o
tests/iconify: tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o
tests/iconify: tests/CMakeFiles/iconify.dir/build.make
tests/iconify: src/libglfw3.a
tests/iconify: tests/CMakeFiles/iconify.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/fernando/dev/cdraw/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable iconify"
	cd /Users/fernando/dev/cdraw/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/iconify.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/iconify.dir/build: tests/iconify
.PHONY : tests/CMakeFiles/iconify.dir/build

tests/CMakeFiles/iconify.dir/clean:
	cd /Users/fernando/dev/cdraw/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/iconify.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/iconify.dir/clean

tests/CMakeFiles/iconify.dir/depend:
	cd /Users/fernando/dev/cdraw/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/fernando/dev/cdraw/vendor/glfw-3.3.8 /Users/fernando/dev/cdraw/vendor/glfw-3.3.8/tests /Users/fernando/dev/cdraw/build /Users/fernando/dev/cdraw/build/tests /Users/fernando/dev/cdraw/build/tests/CMakeFiles/iconify.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/iconify.dir/depend

