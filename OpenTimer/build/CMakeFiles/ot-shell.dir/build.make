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
include CMakeFiles/ot-shell.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ot-shell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ot-shell.dir/flags.make

CMakeFiles/ot-shell.dir/main/shell/shell.cpp.o: CMakeFiles/ot-shell.dir/flags.make
CMakeFiles/ot-shell.dir/main/shell/shell.cpp.o: ../main/shell/shell.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hcx/Codes/OpenTimer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ot-shell.dir/main/shell/shell.cpp.o"
	/usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ot-shell.dir/main/shell/shell.cpp.o -c /home/hcx/Codes/OpenTimer/main/shell/shell.cpp

CMakeFiles/ot-shell.dir/main/shell/shell.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ot-shell.dir/main/shell/shell.cpp.i"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hcx/Codes/OpenTimer/main/shell/shell.cpp > CMakeFiles/ot-shell.dir/main/shell/shell.cpp.i

CMakeFiles/ot-shell.dir/main/shell/shell.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ot-shell.dir/main/shell/shell.cpp.s"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hcx/Codes/OpenTimer/main/shell/shell.cpp -o CMakeFiles/ot-shell.dir/main/shell/shell.cpp.s

# Object files for target ot-shell
ot__shell_OBJECTS = \
"CMakeFiles/ot-shell.dir/main/shell/shell.cpp.o"

# External object files for target ot-shell
ot__shell_EXTERNAL_OBJECTS =

../bin/ot-shell: CMakeFiles/ot-shell.dir/main/shell/shell.cpp.o
../bin/ot-shell: CMakeFiles/ot-shell.dir/build.make
../bin/ot-shell: ../lib/libOpenTimer.a
../bin/ot-shell: CMakeFiles/ot-shell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hcx/Codes/OpenTimer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/ot-shell"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ot-shell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ot-shell.dir/build: ../bin/ot-shell

.PHONY : CMakeFiles/ot-shell.dir/build

CMakeFiles/ot-shell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ot-shell.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ot-shell.dir/clean

CMakeFiles/ot-shell.dir/depend:
	cd /home/hcx/Codes/OpenTimer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hcx/Codes/OpenTimer /home/hcx/Codes/OpenTimer /home/hcx/Codes/OpenTimer/build /home/hcx/Codes/OpenTimer/build /home/hcx/Codes/OpenTimer/build/CMakeFiles/ot-shell.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ot-shell.dir/depend

