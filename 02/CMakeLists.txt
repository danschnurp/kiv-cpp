cmake_minimum_required(VERSION 3.16)
project(kiv-cpp-sp-02)

set(CMAKE_CXX_STANDARD 20)

add_executable(kiv-cpp-sp-02 main.cpp CMemory_Database.h specialized_rows/Row.h specialized_rows/Row.cpp
        specialized_rows/Pair.cpp specialized_rows/Pair.h)


project(kiv-cpp-zk)

set(CMAKE_CXX_STANDARD 20)

add_executable(kiv-cpp-zk zkouska/zk.cpp zkouska/Text.cpp zkouska/Text.h
        zkouska/Veta.cpp zkouska/Veta.h zkouska/AlphabetShiftTransformer.cpp zkouska/AlphabetShiftTransformer.h)
