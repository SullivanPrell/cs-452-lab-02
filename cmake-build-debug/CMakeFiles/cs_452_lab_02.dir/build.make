# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\sulli\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7442.42\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\sulli\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7442.42\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\cs_452_lab_02.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\cs_452_lab_02.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\cs_452_lab_02.dir\flags.make

CMakeFiles\cs_452_lab_02.dir\main.cpp.obj: CMakeFiles\cs_452_lab_02.dir\flags.make
CMakeFiles\cs_452_lab_02.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cs_452_lab_02.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\cs_452_lab_02.dir\main.cpp.obj /FdCMakeFiles\cs_452_lab_02.dir\ /FS -c "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\main.cpp"
<<

CMakeFiles\cs_452_lab_02.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cs_452_lab_02.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\cs_452_lab_02.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\main.cpp"
<<

CMakeFiles\cs_452_lab_02.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cs_452_lab_02.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\cs_452_lab_02.dir\main.cpp.s /c "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\main.cpp"
<<

CMakeFiles\cs_452_lab_02.dir\Queue.cpp.obj: CMakeFiles\cs_452_lab_02.dir\flags.make
CMakeFiles\cs_452_lab_02.dir\Queue.cpp.obj: ..\Queue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cs_452_lab_02.dir/Queue.cpp.obj"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\cs_452_lab_02.dir\Queue.cpp.obj /FdCMakeFiles\cs_452_lab_02.dir\ /FS -c "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\Queue.cpp"
<<

CMakeFiles\cs_452_lab_02.dir\Queue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cs_452_lab_02.dir/Queue.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\cs_452_lab_02.dir\Queue.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\Queue.cpp"
<<

CMakeFiles\cs_452_lab_02.dir\Queue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cs_452_lab_02.dir/Queue.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\cs_452_lab_02.dir\Queue.cpp.s /c "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\Queue.cpp"
<<

CMakeFiles\cs_452_lab_02.dir\process.cpp.obj: CMakeFiles\cs_452_lab_02.dir\flags.make
CMakeFiles\cs_452_lab_02.dir\process.cpp.obj: ..\process.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cs_452_lab_02.dir/process.cpp.obj"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\cs_452_lab_02.dir\process.cpp.obj /FdCMakeFiles\cs_452_lab_02.dir\ /FS -c "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\process.cpp"
<<

CMakeFiles\cs_452_lab_02.dir\process.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cs_452_lab_02.dir/process.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\cs_452_lab_02.dir\process.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\process.cpp"
<<

CMakeFiles\cs_452_lab_02.dir\process.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cs_452_lab_02.dir/process.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\cs_452_lab_02.dir\process.cpp.s /c "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\process.cpp"
<<

# Object files for target cs_452_lab_02
cs_452_lab_02_OBJECTS = \
"CMakeFiles\cs_452_lab_02.dir\main.cpp.obj" \
"CMakeFiles\cs_452_lab_02.dir\Queue.cpp.obj" \
"CMakeFiles\cs_452_lab_02.dir\process.cpp.obj"

# External object files for target cs_452_lab_02
cs_452_lab_02_EXTERNAL_OBJECTS =

cs_452_lab_02.exe: CMakeFiles\cs_452_lab_02.dir\main.cpp.obj
cs_452_lab_02.exe: CMakeFiles\cs_452_lab_02.dir\Queue.cpp.obj
cs_452_lab_02.exe: CMakeFiles\cs_452_lab_02.dir\process.cpp.obj
cs_452_lab_02.exe: CMakeFiles\cs_452_lab_02.dir\build.make
cs_452_lab_02.exe: CMakeFiles\cs_452_lab_02.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable cs_452_lab_02.exe"
	C:\Users\sulli\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7442.42\bin\cmake\win\bin\cmake.exe -E vs_link_exe --intdir=CMakeFiles\cs_452_lab_02.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\cs_452_lab_02.dir\objects1.rsp @<<
 /out:cs_452_lab_02.exe /implib:cs_452_lab_02.lib /pdb:"C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\cmake-build-debug\cs_452_lab_02.pdb" /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\cs_452_lab_02.dir\build: cs_452_lab_02.exe

.PHONY : CMakeFiles\cs_452_lab_02.dir\build

CMakeFiles\cs_452_lab_02.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cs_452_lab_02.dir\cmake_clean.cmake
.PHONY : CMakeFiles\cs_452_lab_02.dir\clean

CMakeFiles\cs_452_lab_02.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02" "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02" "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\cmake-build-debug" "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\cmake-build-debug" "C:\Users\sulli\OneDrive - UW-Eau Claire\Computer Science\cs 452\cs-452-lab-02\cmake-build-debug\CMakeFiles\cs_452_lab_02.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\cs_452_lab_02.dir\depend

