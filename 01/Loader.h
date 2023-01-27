//
// Created by dartix on 10/13/21.
//

#ifndef CPP_SEMWORK1_LOADER_H
#define CPP_SEMWORK1_LOADER_H
#pragma once
#include "Arena.h"
#include "objects/Ball.h"
#include "objects/Rectangle.h"
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>

/**
 * loads config file to structures
 */
class Loader {
private:

    // path to input file
    std::string &inputs;

    std::ifstream file;
    std::unique_ptr<Arena> arena;
    std::vector<Ball> balls;
    std::vector<Rectangle> rectangles;
    std::vector<Square> squares;
    std::string err;

    void load();

    static std::vector<std::string> parseObject(std::string &objectParams);

    void parseObjects( std::vector<std::string> objectParams);


public:

    Loader(std::string &inputs1);

    ~Loader();

    const std::unique_ptr<Arena> &getArena() const;

    const std::string &getErr() const;

    std::vector<Ball> &getBalls();

    std::vector<Rectangle> & getRectangles();

    std::vector<Square> &getSquares();

    void setErr(const std::string &err);

};


#endif //CPP_SEMWORK1_LOADER_H
