project(WaveRadio)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(WaveRadio_SRCS aboutwidget.cpp waveradiobackend.cpp wavewidget.cpp WaveRadio.cpp main.cpp)
qt4_automoc(${WaveRadio_SRCS})
add_executable(WaveRadio ${WaveRadio_SRCS})
target_link_libraries(WaveRadio ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/WaveRadio
DESTINATION /usr/bin)

INSTALL(FILES icons/aol-radio-icon-512x512.png
DESTINATION /usr/share/OpenWave/icons)
