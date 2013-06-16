project(Listener)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})


set(Listener_SRCS audioplayer.cpp networkmanager.cpp Listener.cpp main.cpp)
qt4_automoc(${Listener_SRCS})
add_executable(Listener ${Listener_SRCS})
target_link_libraries(Listener ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY}
${QT_QTNETWORK_LIBRARY} ${QT_QTMULTIMEDIA_LIBRARY})

