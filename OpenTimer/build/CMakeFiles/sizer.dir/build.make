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
include CMakeFiles/sizer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sizer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sizer.dir/flags.make

CMakeFiles/sizer.dir/example/sizer/sizer.cpp.o: CMakeFiles/sizer.dir/flags.make
CMakeFiles/sizer.dir/example/sizer/sizer.cpp.o: ../example/sizer/sizer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hcx/Codes/OpenTimer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sizer.dir/example/sizer/sizer.cpp.o"
	/usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sizer.dir/example/sizer/sizer.cpp.o -c /home/hcx/Codes/OpenTimer/example/sizer/sizer.cpp

CMakeFiles/sizer.dir/example/sizer/sizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sizer.dir/example/sizer/sizer.cpp.i"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hcx/Codes/OpenTimer/example/sizer/sizer.cpp > CMakeFiles/sizer.dir/example/sizer/sizer.cpp.i

CMakeFiles/sizer.dir/example/sizer/sizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sizer.dir/example/sizer/sizer.cpp.s"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hcx/Codes/OpenTimer/example/sizer/sizer.cpp -o CMakeFiles/sizer.dir/example/sizer/sizer.cpp.s

# Object files for target sizer
sizer_OBJECTS = \
"CMakeFiles/sizer.dir/example/sizer/sizer.cpp.o"

# External object files for target sizer
sizer_EXTERNAL_OBJECTS =

../example/sizer/sizer: CMakeFiles/sizer.dir/example/sizer/sizer.cpp.o
../example/sizer/sizer: CMakeFiles/sizer.dir/build.make
../example/sizer/sizer: ../lib/libOpenTimer.a
../example/sizer/sizer: CMakeFiles/sizer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hcx/Codes/OpenTimer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../example/sizer/sizer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sizer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sizer.dir/build: ../example/sizer/sizer

.PHONY : CMakeFiles/sizer.dir/build

CMakeFiles/sizer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sizer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sizer.dir/clean

CMakeFiles/sizer.dir/depend:
	cd /home/hcx/Codes/OpenTimer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hcx/Codes/OpenTimer /home/hcx/Codes/OpenTimer /home/hcx/Codes/OpenTimer/build /home/hcx/Codes/OpenTimer/build /home/hcx/Codes/OpenTimer/build/CMakeFiles/sizer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sizer.dir/depend
