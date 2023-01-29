#
# This CMake file only exists for the IDE to handle the files correctly, please ignore it.
#

cmake_minimum_required(VERSION 3.24)
project(CandleLightEmulator)

set(CMAKE_CXX_STANDARD 17)

include_directories(~/Library/Arduino15/packages/arduino/hardware/avr/1.8.6/cores/arduino)

add_executable(CandleLightEmulator
        Application.cpp
        Application.hpp
        CandleLightEmulator.ino
        Configuration.hpp
        Display.cpp
        Display.hpp
        RandomSuppressor.cpp
        RandomSuppressor.hpp
        RandomWave.cpp
        RandomWave.hpp
        Tools.hpp)
