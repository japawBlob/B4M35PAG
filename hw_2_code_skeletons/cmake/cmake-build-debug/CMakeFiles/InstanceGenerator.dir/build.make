# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /snap/clion/169/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/169/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/cmake/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/InstanceGenerator.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/InstanceGenerator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/InstanceGenerator.dir/flags.make

CMakeFiles/InstanceGenerator.dir/home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp.o: CMakeFiles/InstanceGenerator.dir/flags.make
CMakeFiles/InstanceGenerator.dir/home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp.o: /home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/cmake/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/InstanceGenerator.dir/home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/InstanceGenerator.dir/home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp.o -c /home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp

CMakeFiles/InstanceGenerator.dir/home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/InstanceGenerator.dir/home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp > CMakeFiles/InstanceGenerator.dir/home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp.i

CMakeFiles/InstanceGenerator.dir/home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/InstanceGenerator.dir/home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp -o CMakeFiles/InstanceGenerator.dir/home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp.s

# Object files for target InstanceGenerator
InstanceGenerator_OBJECTS = \
"CMakeFiles/InstanceGenerator.dir/home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp.o"

# External object files for target InstanceGenerator
InstanceGenerator_EXTERNAL_OBJECTS =

InstanceGenerator: CMakeFiles/InstanceGenerator.dir/home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/src/InstanceGenerator.cpp.o
InstanceGenerator: CMakeFiles/InstanceGenerator.dir/build.make
InstanceGenerator: CMakeFiles/InstanceGenerator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/cmake/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable InstanceGenerator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/InstanceGenerator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/InstanceGenerator.dir/build: InstanceGenerator
.PHONY : CMakeFiles/InstanceGenerator.dir/build

CMakeFiles/InstanceGenerator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/InstanceGenerator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/InstanceGenerator.dir/clean

CMakeFiles/InstanceGenerator.dir/depend:
	cd /home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/cmake/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/cmake /home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/cmake /home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/cmake/cmake-build-debug /home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/cmake/cmake-build-debug /home/japaw/Codes/B4M35PAG/hw_2_code_skeletons/cmake/cmake-build-debug/CMakeFiles/InstanceGenerator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/InstanceGenerator.dir/depend
