# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/cmake-3.12.2/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.12.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hcx/Codes/OpenTimer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hcx/Codes/OpenTimer/build

# Include any dependencies generated for this target.
include CMakeFiles/path.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/path.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/path.dir/flags.make

CMakeFiles/path.dir/unittest/path.cpp.o: CMakeFiles/path.dir/flags.make
CMakeFiles/path.dir/unittest/path.cpp.o: ../unittest/path.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hcx/Codes/OpenTimer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/path.dir/unittest/path.cpp.o"
	/usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/path.dir/unittest/path.cpp.o -c /home/hcx/Codes/OpenTimer/unittest/path.cpp

CMakeFiles/path.dir/unittest/path.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/path.dir/unittest/path.cpp.i"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hcx/Codes/OpenTimer/unittest/path.cpp > CMakeFiles/path.dir/unittest/path.cpp.i

CMakeFiles/path.dir/unittest/path.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/path.dir/unittest/path.cpp.s"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hcx/Codes/OpenTimer/unittest/path.cpp -o CMakeFiles/path.dir/unittest/path.cpp.s

# Object files for target path
path_OBJECTS = \
"CMakeFiles/path.dir/unittest/path.cpp.o"

# External object files for target path
path_EXTERNAL_OBJECTS =

../unittest/path: CMakeFiles/path.dir/unittest/path.cpp.o
../unittest/path: CMakeFiles/path.dir/build.make
../unittest/path: ../lib/libOpenTimer.a
../unittest/path: CMakeFiles/path.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hcx/Codes/OpenTimer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../unittest/path"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/path.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/path.dir/build: ../unittest/path

.PHONY : CMakeFiles/path.dir/build

CMakeFiles/path.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/path.dir/cmake_clean.cmake
.PHONY : CMakeFiles/path.dir/clean

CMakeFiles/path.dir/depend:
	cd /home/hcx/Codes/OpenTimer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hcx/Codes/OpenTimer /home/hcx/Codes/OpenTimer /home/hcx/Codes/OpenTimer/build /home/hcx/Codes/OpenTimer/build /home/hcx/Codes/OpenTimer/build/CMakeFiles/path.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/path.dir/depend

