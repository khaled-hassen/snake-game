# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\khaled\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\212.5457.51\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\khaled\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\212.5457.51\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\khaled\Documents\BME\C Programming\snake"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\khaled\Documents\BME\C Programming\snake\cmake-build-release"

# Include any dependencies generated for this target.
include CMakeFiles/snake.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/snake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/snake.dir/flags.make

CMakeFiles/snake.dir/main.c.obj: CMakeFiles/snake.dir/flags.make
CMakeFiles/snake.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\khaled\Documents\BME\C Programming\snake\cmake-build-release\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/snake.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\snake.dir\main.c.obj -c "C:\Users\khaled\Documents\BME\C Programming\snake\main.c"

CMakeFiles/snake.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/snake.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\khaled\Documents\BME\C Programming\snake\main.c" > CMakeFiles\snake.dir\main.c.i

CMakeFiles/snake.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/snake.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\khaled\Documents\BME\C Programming\snake\main.c" -o CMakeFiles\snake.dir\main.c.s

CMakeFiles/snake.dir/libs/game/game.c.obj: CMakeFiles/snake.dir/flags.make
CMakeFiles/snake.dir/libs/game/game.c.obj: ../libs/game/game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\khaled\Documents\BME\C Programming\snake\cmake-build-release\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/snake.dir/libs/game/game.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\snake.dir\libs\game\game.c.obj -c "C:\Users\khaled\Documents\BME\C Programming\snake\libs\game\game.c"

CMakeFiles/snake.dir/libs/game/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/snake.dir/libs/game/game.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\khaled\Documents\BME\C Programming\snake\libs\game\game.c" > CMakeFiles\snake.dir\libs\game\game.c.i

CMakeFiles/snake.dir/libs/game/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/snake.dir/libs/game/game.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\khaled\Documents\BME\C Programming\snake\libs\game\game.c" -o CMakeFiles\snake.dir\libs\game\game.c.s

CMakeFiles/snake.dir/libs/snake/snake.c.obj: CMakeFiles/snake.dir/flags.make
CMakeFiles/snake.dir/libs/snake/snake.c.obj: ../libs/snake/snake.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\khaled\Documents\BME\C Programming\snake\cmake-build-release\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/snake.dir/libs/snake/snake.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\snake.dir\libs\snake\snake.c.obj -c "C:\Users\khaled\Documents\BME\C Programming\snake\libs\snake\snake.c"

CMakeFiles/snake.dir/libs/snake/snake.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/snake.dir/libs/snake/snake.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\khaled\Documents\BME\C Programming\snake\libs\snake\snake.c" > CMakeFiles\snake.dir\libs\snake\snake.c.i

CMakeFiles/snake.dir/libs/snake/snake.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/snake.dir/libs/snake/snake.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\khaled\Documents\BME\C Programming\snake\libs\snake\snake.c" -o CMakeFiles\snake.dir\libs\snake\snake.c.s

CMakeFiles/snake.dir/libs/apple/apple.c.obj: CMakeFiles/snake.dir/flags.make
CMakeFiles/snake.dir/libs/apple/apple.c.obj: ../libs/apple/apple.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\khaled\Documents\BME\C Programming\snake\cmake-build-release\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/snake.dir/libs/apple/apple.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\snake.dir\libs\apple\apple.c.obj -c "C:\Users\khaled\Documents\BME\C Programming\snake\libs\apple\apple.c"

CMakeFiles/snake.dir/libs/apple/apple.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/snake.dir/libs/apple/apple.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\khaled\Documents\BME\C Programming\snake\libs\apple\apple.c" > CMakeFiles\snake.dir\libs\apple\apple.c.i

CMakeFiles/snake.dir/libs/apple/apple.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/snake.dir/libs/apple/apple.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\khaled\Documents\BME\C Programming\snake\libs\apple\apple.c" -o CMakeFiles\snake.dir\libs\apple\apple.c.s

CMakeFiles/snake.dir/libs/utils/math/math.c.obj: CMakeFiles/snake.dir/flags.make
CMakeFiles/snake.dir/libs/utils/math/math.c.obj: ../libs/utils/math/math.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\khaled\Documents\BME\C Programming\snake\cmake-build-release\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/snake.dir/libs/utils/math/math.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\snake.dir\libs\utils\math\math.c.obj -c "C:\Users\khaled\Documents\BME\C Programming\snake\libs\utils\math\math.c"

CMakeFiles/snake.dir/libs/utils/math/math.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/snake.dir/libs/utils/math/math.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\khaled\Documents\BME\C Programming\snake\libs\utils\math\math.c" > CMakeFiles\snake.dir\libs\utils\math\math.c.i

CMakeFiles/snake.dir/libs/utils/math/math.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/snake.dir/libs/utils/math/math.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\khaled\Documents\BME\C Programming\snake\libs\utils\math\math.c" -o CMakeFiles\snake.dir\libs\utils\math\math.c.s

# Object files for target snake
snake_OBJECTS = \
"CMakeFiles/snake.dir/main.c.obj" \
"CMakeFiles/snake.dir/libs/game/game.c.obj" \
"CMakeFiles/snake.dir/libs/snake/snake.c.obj" \
"CMakeFiles/snake.dir/libs/apple/apple.c.obj" \
"CMakeFiles/snake.dir/libs/utils/math/math.c.obj"

# External object files for target snake
snake_EXTERNAL_OBJECTS =

snake.exe: CMakeFiles/snake.dir/main.c.obj
snake.exe: CMakeFiles/snake.dir/libs/game/game.c.obj
snake.exe: CMakeFiles/snake.dir/libs/snake/snake.c.obj
snake.exe: CMakeFiles/snake.dir/libs/apple/apple.c.obj
snake.exe: CMakeFiles/snake.dir/libs/utils/math/math.c.obj
snake.exe: CMakeFiles/snake.dir/build.make
snake.exe: CMakeFiles/snake.dir/linklibs.rsp
snake.exe: CMakeFiles/snake.dir/objects1.rsp
snake.exe: CMakeFiles/snake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\khaled\Documents\BME\C Programming\snake\cmake-build-release\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable snake.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\snake.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/snake.dir/build: snake.exe
.PHONY : CMakeFiles/snake.dir/build

CMakeFiles/snake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\snake.dir\cmake_clean.cmake
.PHONY : CMakeFiles/snake.dir/clean

CMakeFiles/snake.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\khaled\Documents\BME\C Programming\snake" "C:\Users\khaled\Documents\BME\C Programming\snake" "C:\Users\khaled\Documents\BME\C Programming\snake\cmake-build-release" "C:\Users\khaled\Documents\BME\C Programming\snake\cmake-build-release" "C:\Users\khaled\Documents\BME\C Programming\snake\cmake-build-release\CMakeFiles\snake.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/snake.dir/depend

