# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cdf/muduo-master/examples/curl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cdf/muduo-master/examples/curl

# Include any dependencies generated for this target.
include CMakeFiles/curl_download.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/curl_download.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/curl_download.dir/flags.make

CMakeFiles/curl_download.dir/download.o: CMakeFiles/curl_download.dir/flags.make
CMakeFiles/curl_download.dir/download.o: download.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cdf/muduo-master/examples/curl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/curl_download.dir/download.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/curl_download.dir/download.o -c /home/cdf/muduo-master/examples/curl/download.cc

CMakeFiles/curl_download.dir/download.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/curl_download.dir/download.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cdf/muduo-master/examples/curl/download.cc > CMakeFiles/curl_download.dir/download.i

CMakeFiles/curl_download.dir/download.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/curl_download.dir/download.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cdf/muduo-master/examples/curl/download.cc -o CMakeFiles/curl_download.dir/download.s

CMakeFiles/curl_download.dir/download.o.requires:

.PHONY : CMakeFiles/curl_download.dir/download.o.requires

CMakeFiles/curl_download.dir/download.o.provides: CMakeFiles/curl_download.dir/download.o.requires
	$(MAKE) -f CMakeFiles/curl_download.dir/build.make CMakeFiles/curl_download.dir/download.o.provides.build
.PHONY : CMakeFiles/curl_download.dir/download.o.provides

CMakeFiles/curl_download.dir/download.o.provides.build: CMakeFiles/curl_download.dir/download.o


# Object files for target curl_download
curl_download_OBJECTS = \
"CMakeFiles/curl_download.dir/download.o"

# External object files for target curl_download
curl_download_EXTERNAL_OBJECTS =

curl_download: CMakeFiles/curl_download.dir/download.o
curl_download: CMakeFiles/curl_download.dir/build.make
curl_download: libmuduo_curl.a
curl_download: CMakeFiles/curl_download.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cdf/muduo-master/examples/curl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable curl_download"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/curl_download.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/curl_download.dir/build: curl_download

.PHONY : CMakeFiles/curl_download.dir/build

CMakeFiles/curl_download.dir/requires: CMakeFiles/curl_download.dir/download.o.requires

.PHONY : CMakeFiles/curl_download.dir/requires

CMakeFiles/curl_download.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/curl_download.dir/cmake_clean.cmake
.PHONY : CMakeFiles/curl_download.dir/clean

CMakeFiles/curl_download.dir/depend:
	cd /home/cdf/muduo-master/examples/curl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cdf/muduo-master/examples/curl /home/cdf/muduo-master/examples/curl /home/cdf/muduo-master/examples/curl /home/cdf/muduo-master/examples/curl /home/cdf/muduo-master/examples/curl/CMakeFiles/curl_download.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/curl_download.dir/depend

