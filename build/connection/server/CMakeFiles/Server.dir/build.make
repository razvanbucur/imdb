# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/root/imdb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/root/imdb/build

# Include any dependencies generated for this target.
include connection/server/CMakeFiles/Server.dir/depend.make

# Include the progress variables for this target.
include connection/server/CMakeFiles/Server.dir/progress.make

# Include the compile flags for this target's objects.
include connection/server/CMakeFiles/Server.dir/flags.make

connection/server/CMakeFiles/Server.dir/Server.cpp.o: connection/server/CMakeFiles/Server.dir/flags.make
connection/server/CMakeFiles/Server.dir/Server.cpp.o: ../connection/server/Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/root/imdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object connection/server/CMakeFiles/Server.dir/Server.cpp.o"
	cd /home/root/imdb/build/connection/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Server.cpp.o -c /home/root/imdb/connection/server/Server.cpp

connection/server/CMakeFiles/Server.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Server.cpp.i"
	cd /home/root/imdb/build/connection/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/root/imdb/connection/server/Server.cpp > CMakeFiles/Server.dir/Server.cpp.i

connection/server/CMakeFiles/Server.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Server.cpp.s"
	cd /home/root/imdb/build/connection/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/root/imdb/connection/server/Server.cpp -o CMakeFiles/Server.dir/Server.cpp.s

connection/server/CMakeFiles/Server.dir/MainServer.cpp.o: connection/server/CMakeFiles/Server.dir/flags.make
connection/server/CMakeFiles/Server.dir/MainServer.cpp.o: ../connection/server/MainServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/root/imdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object connection/server/CMakeFiles/Server.dir/MainServer.cpp.o"
	cd /home/root/imdb/build/connection/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/MainServer.cpp.o -c /home/root/imdb/connection/server/MainServer.cpp

connection/server/CMakeFiles/Server.dir/MainServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/MainServer.cpp.i"
	cd /home/root/imdb/build/connection/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/root/imdb/connection/server/MainServer.cpp > CMakeFiles/Server.dir/MainServer.cpp.i

connection/server/CMakeFiles/Server.dir/MainServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/MainServer.cpp.s"
	cd /home/root/imdb/build/connection/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/root/imdb/connection/server/MainServer.cpp -o CMakeFiles/Server.dir/MainServer.cpp.s

# Object files for target Server
Server_OBJECTS = \
"CMakeFiles/Server.dir/Server.cpp.o" \
"CMakeFiles/Server.dir/MainServer.cpp.o"

# External object files for target Server
Server_EXTERNAL_OBJECTS =

connection/server/Server: connection/server/CMakeFiles/Server.dir/Server.cpp.o
connection/server/Server: connection/server/CMakeFiles/Server.dir/MainServer.cpp.o
connection/server/Server: connection/server/CMakeFiles/Server.dir/build.make
connection/server/Server: connection/server/CMakeFiles/Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/root/imdb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Server"
	cd /home/root/imdb/build/connection/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
connection/server/CMakeFiles/Server.dir/build: connection/server/Server

.PHONY : connection/server/CMakeFiles/Server.dir/build

connection/server/CMakeFiles/Server.dir/clean:
	cd /home/root/imdb/build/connection/server && $(CMAKE_COMMAND) -P CMakeFiles/Server.dir/cmake_clean.cmake
.PHONY : connection/server/CMakeFiles/Server.dir/clean

connection/server/CMakeFiles/Server.dir/depend:
	cd /home/root/imdb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/root/imdb /home/root/imdb/connection/server /home/root/imdb/build /home/root/imdb/build/connection/server /home/root/imdb/build/connection/server/CMakeFiles/Server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : connection/server/CMakeFiles/Server.dir/depend
