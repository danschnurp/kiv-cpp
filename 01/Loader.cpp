//
// Created by dartix on 10/13/21.
//


#include <regex>
#include "Loader.h"


Loader::Loader(std::string &inputs1) : inputs(inputs1) {
    file.open(inputs, std::ios::in);
    load();

}


Loader::~Loader() {
    file.close();
}

void Loader::load() {
    std::string line;
    std::vector<std::string> params;
    try {
        while (std::getline(file, line)) {
            int pos = static_cast<int>(line.find('\r'));
            /* Removing the carriage return character from the line. */
            if (pos > 0) line = line.replace(pos, pos + 1, "");
            if (line == "OBJECTS") break;

            /* This is checking if the line starts with a # or < or ARENA. If it does, it will not be added to the vector. */
            if (!line.starts_with('#') && !line.starts_with('<') && line != "ARENA") {
                if (line.find(' ') <= line.length()) {
                    params.emplace_back(line.substr(0, line.find(' ')));
                    params.emplace_back(line.substr(line.find(' ') + 1, line.find('\n')));
                } else {
                    params.emplace_back(line);
                }
            }
        }
        bool check = false;
        /* Checking if there is a carriage return character in the vector. */
        std::for_each(params.begin(), params.end(), [&](const auto& item){if (item == "\r") check = true;});
        if (params.empty() || check)
            throw std::string{""};
        /* Creating a new arena object with the parameters from the file. */
        arena = std::make_unique<Arena>(std::stof(params[0]),std::stof(params[1]),
                                        std::stof(params[2]),std::stoi(params[3]));
        for (const auto &item: params) {
            /* Checking if the string "end_after_collision" is in the line. */
            if (item.find("end_after_collision") <= line.length()) {
                arena->setEndAfterCollision(true);
            /* Checking if the string "report_distance" is in the line. */
            } else if (item.find("report_distance") <= line.length()) {
                arena->setReportDistance(true);
            }
        }
        // objects
        std::vector<std::string> objectParams;
        while (std::getline(file, line)) {
            int pos = static_cast<int>(line.find('\r'));
            if (pos > 0) line = line.replace(pos, pos + 1, "");
            if (!line.starts_with('#') && !line.starts_with('<') && line != "OBJECTS") {
                objectParams.emplace_back(line);
            }
        }
        parseObjects(objectParams);
    }
    catch (std::invalid_argument &error) {
        err =  "err while parsing file...";
        return;
    }
    catch (std::logic_error &error) {
        err = "err while parsing file...";
        return;
    }
    catch (std::string &error) {
        err = "err while parsing file...";
        return;
    }
}


/**
 * It takes a string and returns a vector of strings, where each string is a word from the original string
 *
 * @param objectParams The string containing the parameters of the object.
 *
 * @return A vector of strings.
 */
std::vector<std::string> Loader::parseObject(std::string &objectParams) {
    std::stringstream ss(objectParams);
    std::vector<std::string> parsed;
    std::string word;
    while (ss >> word) parsed.emplace_back(word);
    return parsed;
}

/**
 * It parses the objects in the file and adds them to the appropriate vector
 *
 * @param objectParams a vector of strings that contains the parameters for the objects
 */
void Loader::parseObjects(std::vector<std::string> objectParams) {
    for (int j = 0; j < objectParams.size(); j++) {
        /* Checking if the string "ball" is in the line. */
        if (objectParams[j] == "ball") {
            int count = std::stoi(objectParams[++j]);
            for (int i = 0; i < count; i++) {
                std::vector<std::string> parsed = parseObject(objectParams[++j]);
                std::vector<float> loc = {std::stof(parsed[1]), std::stof(parsed[2])};
                std::vector<float> speed = {std::stof(parsed[3]), std::stof(parsed[4])};
                balls.emplace_back(
                        parsed[0], loc, loc, speed, std::stod(parsed[5]),
                        std::stod(parsed[6]), std::stof(parsed[7]));
            }
        /* Checking if the string "square" is in the line. */
        } else if (objectParams[j] == "square") {
            int count = std::stoi(objectParams[++j]);
            for (int i = 0; i < count; i++) {
                std::vector<std::string> parsed = parseObject(objectParams[++j]);
                std::vector<float> loc = {std::stof(parsed[1]), std::stof(parsed[2])};
                std::vector<float> speed = {std::stof(parsed[3]), std::stof(parsed[4])};
                /* Adding a new square object to the vector of squares. */
                squares.emplace_back(
                        parsed[0], loc, loc, speed, std::stod(parsed[5]),
                        std::stod(parsed[6]), std::stod(parsed[7]));
            }
        /* Checking if the string "rectangle" is in the line. */
        } else if (objectParams[j] == "rectangle") {
            int count = std::stoi(objectParams[++j]);
            for (int i = 0; i < count; i++) {
                std::vector<std::string> parsed = parseObject(objectParams[++j]);
                if (parsed.empty())
                    throw std::string{ "" };
                std::vector<float> loc = {std::stof(parsed[1]), std::stof(parsed[2])};
                std::vector<float> speed = {std::stof(parsed[3]), std::stof(parsed[4])};
                rectangles.emplace_back(
                        parsed[0], loc, loc, speed, std::stod(parsed[5]),
                        std::stod(parsed[6]), std::stod(parsed[7]), std::stod(parsed[8]));
            }
        }
    }
}

const std::unique_ptr<Arena> &Loader::getArena() const {
    return arena;
}

std::vector<Ball> & Loader::getBalls() {
    return balls;
}

std::vector<Rectangle> & Loader::getRectangles() {
    return rectangles;
}

std::vector<Square> & Loader::getSquares() {
    return squares;
}

const std::string &Loader::getErr() const {
    return err;
}

void Loader::setErr(const std::string &err) {
    Loader::err = err;
}

