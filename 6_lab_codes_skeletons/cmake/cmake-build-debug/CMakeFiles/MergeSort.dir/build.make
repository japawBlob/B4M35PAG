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
CMAKE_SOURCE_DIR = /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MergeSort.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/MergeSort.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MergeSort.dir/flags.make

CMakeFiles/MergeSort.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp.o: CMakeFiles/MergeSort.dir/flags.make
CMakeFiles/MergeSort.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp.o: /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MergeSort.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MergeSort.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp.o -c /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp

CMakeFiles/MergeSort.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MergeSort.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp > CMakeFiles/MergeSort.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp.i

CMakeFiles/MergeSort.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MergeSort.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp -o CMakeFiles/MergeSort.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp.s

# Object files for target MergeSort
MergeSort_OBJECTS = \
"CMakeFiles/MergeSort.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp.o"

# External object files for target MergeSort
MergeSort_EXTERNAL_OBJECTS =

MergeSort: CMakeFiles/MergeSort.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/MergeSort.cpp.o
MergeSort: CMakeFiles/MergeSort.dir/build.make
MergeSort: CMakeFiles/MergeSort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MergeSort"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MergeSort.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MergeSort.dir/build: MergeSort
.PHONY : CMakeFiles/MergeSort.dir/build

CMakeFiles/MergeSort.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MergeSort.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MergeSort.dir/clean

CMakeFiles/MergeSort.dir/depend:
	cd /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake/cmake-build-debug /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake/cmake-build-debug /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake/cmake-build-debug/CMakeFiles/MergeSort.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MergeSort.dir/depend

