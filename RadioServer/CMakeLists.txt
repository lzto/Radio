project(RadioServer)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(RadioServer_SRCS networkmanager.cpp radioinput.cpp RadioServer.cpp main.cpp)
qt4_automoc(${RadioServer_SRCS})
add_executable(RadioServer ${RadioServer_SRCS})
target_link_libraries(RadioServer
	${QT_QTCORE_LIBRARY}
	${QT_QTMULTIMEDIA_LIBRARY}
	${QT_QTNETWORK_LIBRARY}
	)
