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
include CMakeFiles/VectorNormalization.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/VectorNormalization.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VectorNormalization.dir/flags.make

CMakeFiles/VectorNormalization.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp.o: CMakeFiles/VectorNormalization.dir/flags.make
CMakeFiles/VectorNormalization.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp.o: /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VectorNormalization.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/VectorNormalization.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp.o -c /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp

CMakeFiles/VectorNormalization.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VectorNormalization.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp > CMakeFiles/VectorNormalization.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp.i

CMakeFiles/VectorNormalization.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VectorNormalization.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp -o CMakeFiles/VectorNormalization.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp.s

# Object files for target VectorNormalization
VectorNormalization_OBJECTS = \
"CMakeFiles/VectorNormalization.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp.o"

# External object files for target VectorNormalization
VectorNormalization_EXTERNAL_OBJECTS =

VectorNormalization: CMakeFiles/VectorNormalization.dir/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/src/VectorNormalization.cpp.o
VectorNormalization: CMakeFiles/VectorNormalization.dir/build.make
VectorNormalization: CMakeFiles/VectorNormalization.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VectorNormalization"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VectorNormalization.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VectorNormalization.dir/build: VectorNormalization
.PHONY : CMakeFiles/VectorNormalization.dir/build

CMakeFiles/VectorNormalization.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VectorNormalization.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VectorNormalization.dir/clean

CMakeFiles/VectorNormalization.dir/depend:
	cd /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake/cmake-build-debug /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake/cmake-build-debug /home/japaw/Codes/B4M35PAG/6_lab_codes_skeletons/cmake/cmake-build-debug/CMakeFiles/VectorNormalization.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VectorNormalization.dir/depend

