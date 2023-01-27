cmake_minimum_required(VERSION 3.16)
project(kiv-cpp-sp-01)

set(CMAKE_CXX_STANDARD 20)

add_executable(kiv-cpp-sp-01 main.cpp Arena.cpp Arena.h
        objects/GenericObject.cpp objects/GenericObject.h
        objects/Ball.cpp objects/Ball.h objects/Square.cpp objects/Square.h
        objects/Rectangle.cpp objects/Rectangle.h Loader.cpp
        Loader.h Validator.cpp Validator.h Simulation.cpp Simulation.h)
