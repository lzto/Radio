# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lovewilliam/Develop/Radio/RadioServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lovewilliam/Develop/Radio/RadioServer/build

# Include any dependencies generated for this target.
include CMakeFiles/RadioServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RadioServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RadioServer.dir/flags.make

CMakeFiles/RadioServer.dir/networkmanager.cpp.o: CMakeFiles/RadioServer.dir/flags.make
CMakeFiles/RadioServer.dir/networkmanager.cpp.o: ../networkmanager.cpp
CMakeFiles/RadioServer.dir/networkmanager.cpp.o: networkmanager.moc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lovewilliam/Develop/Radio/RadioServer/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/RadioServer.dir/networkmanager.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RadioServer.dir/networkmanager.cpp.o -c /home/lovewilliam/Develop/Radio/RadioServer/networkmanager.cpp

CMakeFiles/RadioServer.dir/networkmanager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RadioServer.dir/networkmanager.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lovewilliam/Develop/Radio/RadioServer/networkmanager.cpp > CMakeFiles/RadioServer.dir/networkmanager.cpp.i

CMakeFiles/RadioServer.dir/networkmanager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RadioServer.dir/networkmanager.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lovewilliam/Develop/Radio/RadioServer/networkmanager.cpp -o CMakeFiles/RadioServer.dir/networkmanager.cpp.s

CMakeFiles/RadioServer.dir/networkmanager.cpp.o.requires:
.PHONY : CMakeFiles/RadioServer.dir/networkmanager.cpp.o.requires

CMakeFiles/RadioServer.dir/networkmanager.cpp.o.provides: CMakeFiles/RadioServer.dir/networkmanager.cpp.o.requires
	$(MAKE) -f CMakeFiles/RadioServer.dir/build.make CMakeFiles/RadioServer.dir/networkmanager.cpp.o.provides.build
.PHONY : CMakeFiles/RadioServer.dir/networkmanager.cpp.o.provides

CMakeFiles/RadioServer.dir/networkmanager.cpp.o.provides.build: CMakeFiles/RadioServer.dir/networkmanager.cpp.o

CMakeFiles/RadioServer.dir/radioinput.cpp.o: CMakeFiles/RadioServer.dir/flags.make
CMakeFiles/RadioServer.dir/radioinput.cpp.o: ../radioinput.cpp
CMakeFiles/RadioServer.dir/radioinput.cpp.o: radioinput.moc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lovewilliam/Develop/Radio/RadioServer/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/RadioServer.dir/radioinput.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RadioServer.dir/radioinput.cpp.o -c /home/lovewilliam/Develop/Radio/RadioServer/radioinput.cpp

CMakeFiles/RadioServer.dir/radioinput.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RadioServer.dir/radioinput.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lovewilliam/Develop/Radio/RadioServer/radioinput.cpp > CMakeFiles/RadioServer.dir/radioinput.cpp.i

CMakeFiles/RadioServer.dir/radioinput.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RadioServer.dir/radioinput.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lovewilliam/Develop/Radio/RadioServer/radioinput.cpp -o CMakeFiles/RadioServer.dir/radioinput.cpp.s

CMakeFiles/RadioServer.dir/radioinput.cpp.o.requires:
.PHONY : CMakeFiles/RadioServer.dir/radioinput.cpp.o.requires

CMakeFiles/RadioServer.dir/radioinput.cpp.o.provides: CMakeFiles/RadioServer.dir/radioinput.cpp.o.requires
	$(MAKE) -f CMakeFiles/RadioServer.dir/build.make CMakeFiles/RadioServer.dir/radioinput.cpp.o.provides.build
.PHONY : CMakeFiles/RadioServer.dir/radioinput.cpp.o.provides

CMakeFiles/RadioServer.dir/radioinput.cpp.o.provides.build: CMakeFiles/RadioServer.dir/radioinput.cpp.o

CMakeFiles/RadioServer.dir/RadioServer.cpp.o: CMakeFiles/RadioServer.dir/flags.make
CMakeFiles/RadioServer.dir/RadioServer.cpp.o: ../RadioServer.cpp
CMakeFiles/RadioServer.dir/RadioServer.cpp.o: RadioServer.moc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lovewilliam/Develop/Radio/RadioServer/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/RadioServer.dir/RadioServer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RadioServer.dir/RadioServer.cpp.o -c /home/lovewilliam/Develop/Radio/RadioServer/RadioServer.cpp

CMakeFiles/RadioServer.dir/RadioServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RadioServer.dir/RadioServer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lovewilliam/Develop/Radio/RadioServer/RadioServer.cpp > CMakeFiles/RadioServer.dir/RadioServer.cpp.i

CMakeFiles/RadioServer.dir/RadioServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RadioServer.dir/RadioServer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lovewilliam/Develop/Radio/RadioServer/RadioServer.cpp -o CMakeFiles/RadioServer.dir/RadioServer.cpp.s

CMakeFiles/RadioServer.dir/RadioServer.cpp.o.requires:
.PHONY : CMakeFiles/RadioServer.dir/RadioServer.cpp.o.requires

CMakeFiles/RadioServer.dir/RadioServer.cpp.o.provides: CMakeFiles/RadioServer.dir/RadioServer.cpp.o.requires
	$(MAKE) -f CMakeFiles/RadioServer.dir/build.make CMakeFiles/RadioServer.dir/RadioServer.cpp.o.provides.build
.PHONY : CMakeFiles/RadioServer.dir/RadioServer.cpp.o.provides

CMakeFiles/RadioServer.dir/RadioServer.cpp.o.provides.build: CMakeFiles/RadioServer.dir/RadioServer.cpp.o

CMakeFiles/RadioServer.dir/main.cpp.o: CMakeFiles/RadioServer.dir/flags.make
CMakeFiles/RadioServer.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lovewilliam/Develop/Radio/RadioServer/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/RadioServer.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/RadioServer.dir/main.cpp.o -c /home/lovewilliam/Develop/Radio/RadioServer/main.cpp

CMakeFiles/RadioServer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RadioServer.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lovewilliam/Develop/Radio/RadioServer/main.cpp > CMakeFiles/RadioServer.dir/main.cpp.i

CMakeFiles/RadioServer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RadioServer.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lovewilliam/Develop/Radio/RadioServer/main.cpp -o CMakeFiles/RadioServer.dir/main.cpp.s

CMakeFiles/RadioServer.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/RadioServer.dir/main.cpp.o.requires

CMakeFiles/RadioServer.dir/main.cpp.o.provides: CMakeFiles/RadioServer.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/RadioServer.dir/build.make CMakeFiles/RadioServer.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/RadioServer.dir/main.cpp.o.provides

CMakeFiles/RadioServer.dir/main.cpp.o.provides.build: CMakeFiles/RadioServer.dir/main.cpp.o

networkmanager.moc: ../networkmanager.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lovewilliam/Develop/Radio/RadioServer/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating networkmanager.moc"
	/usr/bin/moc -I/usr/include/qt4/QtDesigner -I/usr/include/qt4/QtDeclarative -I/usr/include/qt4/QtScriptTools -I/usr/include/qt4/QtDBus -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtSql -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4/QtMultimedia -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtXmlPatterns -I/usr/include/qt4/QtWebKit -I/usr/include/qt4/QtHelp -I/usr/include/qt4/QtUiTools -I/usr/include/qt4/QtTest -I/usr/include/qt4/QtScript -I/usr/include/qt4/QtSvg -I/usr/include/qt4/Qt3Support -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtCore -I/usr/share/qt4/mkspecs/default -I/usr/include/qt4 -I/home/lovewilliam/Develop/Radio/RadioServer/build -o /home/lovewilliam/Develop/Radio/RadioServer/build/networkmanager.moc /home/lovewilliam/Develop/Radio/RadioServer/networkmanager.h

radioinput.moc: ../radioinput.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lovewilliam/Develop/Radio/RadioServer/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating radioinput.moc"
	/usr/bin/moc -I/usr/include/qt4/QtDesigner -I/usr/include/qt4/QtDeclarative -I/usr/include/qt4/QtScriptTools -I/usr/include/qt4/QtDBus -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtSql -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4/QtMultimedia -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtXmlPatterns -I/usr/include/qt4/QtWebKit -I/usr/include/qt4/QtHelp -I/usr/include/qt4/QtUiTools -I/usr/include/qt4/QtTest -I/usr/include/qt4/QtScript -I/usr/include/qt4/QtSvg -I/usr/include/qt4/Qt3Support -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtCore -I/usr/share/qt4/mkspecs/default -I/usr/include/qt4 -I/home/lovewilliam/Develop/Radio/RadioServer/build -o /home/lovewilliam/Develop/Radio/RadioServer/build/radioinput.moc /home/lovewilliam/Develop/Radio/RadioServer/radioinput.h

RadioServer.moc: ../RadioServer.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lovewilliam/Develop/Radio/RadioServer/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating RadioServer.moc"
	/usr/bin/moc -I/usr/include/qt4/QtDesigner -I/usr/include/qt4/QtDeclarative -I/usr/include/qt4/QtScriptTools -I/usr/include/qt4/QtDBus -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtSql -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4/QtMultimedia -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtXmlPatterns -I/usr/include/qt4/QtWebKit -I/usr/include/qt4/QtHelp -I/usr/include/qt4/QtUiTools -I/usr/include/qt4/QtTest -I/usr/include/qt4/QtScript -I/usr/include/qt4/QtSvg -I/usr/include/qt4/Qt3Support -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtCore -I/usr/share/qt4/mkspecs/default -I/usr/include/qt4 -I/home/lovewilliam/Develop/Radio/RadioServer/build -o /home/lovewilliam/Develop/Radio/RadioServer/build/RadioServer.moc /home/lovewilliam/Develop/Radio/RadioServer/RadioServer.h

# Object files for target RadioServer
RadioServer_OBJECTS = \
"CMakeFiles/RadioServer.dir/networkmanager.cpp.o" \
"CMakeFiles/RadioServer.dir/radioinput.cpp.o" \
"CMakeFiles/RadioServer.dir/RadioServer.cpp.o" \
"CMakeFiles/RadioServer.dir/main.cpp.o"

# External object files for target RadioServer
RadioServer_EXTERNAL_OBJECTS =

RadioServer: CMakeFiles/RadioServer.dir/networkmanager.cpp.o
RadioServer: CMakeFiles/RadioServer.dir/radioinput.cpp.o
RadioServer: CMakeFiles/RadioServer.dir/RadioServer.cpp.o
RadioServer: CMakeFiles/RadioServer.dir/main.cpp.o
RadioServer: /usr/lib/qt4/libQtCore.so
RadioServer: /usr/lib/qt4/libQtMultimedia.so
RadioServer: /usr/lib/qt4/libQtNetwork.so
RadioServer: CMakeFiles/RadioServer.dir/build.make
RadioServer: CMakeFiles/RadioServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable RadioServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RadioServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RadioServer.dir/build: RadioServer
.PHONY : CMakeFiles/RadioServer.dir/build

CMakeFiles/RadioServer.dir/requires: CMakeFiles/RadioServer.dir/networkmanager.cpp.o.requires
CMakeFiles/RadioServer.dir/requires: CMakeFiles/RadioServer.dir/radioinput.cpp.o.requires
CMakeFiles/RadioServer.dir/requires: CMakeFiles/RadioServer.dir/RadioServer.cpp.o.requires
CMakeFiles/RadioServer.dir/requires: CMakeFiles/RadioServer.dir/main.cpp.o.requires
.PHONY : CMakeFiles/RadioServer.dir/requires

CMakeFiles/RadioServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RadioServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RadioServer.dir/clean

CMakeFiles/RadioServer.dir/depend: networkmanager.moc
CMakeFiles/RadioServer.dir/depend: radioinput.moc
CMakeFiles/RadioServer.dir/depend: RadioServer.moc
	cd /home/lovewilliam/Develop/Radio/RadioServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lovewilliam/Develop/Radio/RadioServer /home/lovewilliam/Develop/Radio/RadioServer /home/lovewilliam/Develop/Radio/RadioServer/build /home/lovewilliam/Develop/Radio/RadioServer/build /home/lovewilliam/Develop/Radio/RadioServer/build/CMakeFiles/RadioServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RadioServer.dir/depend

