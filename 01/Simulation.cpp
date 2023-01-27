//
// Created by dartix on 01/01/2022.
//

#include "Simulation.h"


/**
 * A constructor for the Simulation class.
 *
 * @param Loader The loader object that will be used to load the simulation.
 */
Simulation::Simulation(std::shared_ptr<Loader> loader) {

    arena = std::make_unique<Arena>(*loader->getArena());

    for (virtualTime = 0; virtualTime < arena->getMaxSteps(); virtualTime++) {
        if (!loader->getRectangles().empty()) {
            for (Rectangle & item : loader->getRectangles()) {
                if (virtualTime < item.getHideTime() && virtualTime > item.getRevealTime()) {
                    wallReflection(item);
                    moveObj(item);
                }
                else {
                    if (item.getSpeed()[0] == 0 && item.getSpeed()[1] == 0)
                        item.setSpeed({0,0});
                }

            }
            if(checkCollisions(loader->getRectangles(), virtualTime))
                return;
        }

        else if (!loader->getBalls().empty()) {
            for (Ball & item : loader->getBalls()) {
                if (virtualTime < item.getHideTime() && virtualTime > item.getRevealTime()) {
                    wallReflection(item);
                    moveObj(item);
                }
                else {
                    if (item.getSpeed()[0] == 0 && item.getSpeed()[1] == 0)
                        item.setSpeed({0,0});
                }
            }
            if (checkCollisions(loader->getBalls(), virtualTime)) {
                return;
            };
        }
        else if (!loader->getSquares().empty()) {
                for (Square & item : loader->getSquares()) {
                    if (virtualTime < item.getHideTime() && virtualTime > item.getRevealTime()) {
                        wallReflection(item);
                        moveObj(item);
                    }
                    else {
                        if (item.getSpeed()[0] == 0 && item.getSpeed()[1] == 0)
                            item.setSpeed({0,0});
                    }
                }
                if (checkCollisions(loader->getSquares(), virtualTime)) {
                    return;
                };
        }
    }
}

std::vector<float> newLocation(std::vector<float>currentLoc, std::vector<float> speed, float stepSize) {
    return std::vector<float>{currentLoc[0] + speed[0] * stepSize,
                              currentLoc[1] + speed[1] * stepSize};
}

double countDist(std::vector<float> speed, float stepSize) {
    // Pythagorean formula
    return std::sqrt(std::pow(speed[0], 2) + std::pow(speed[1], 2)) * stepSize;
}


void Simulation::moveObj(GenericObject &item) {
    float stepSize = arena->getStepLen();
            if (item.getStepDistance() == 0)
            item.setStepDistance(countDist(item.getSpeed(), stepSize));
        double a = item.getStepDistance() + item.getDistance();
        item.setDistance(a);
        item.setStartLocation(item.getCurrentLocation());
        item.setCurrentLocation(newLocation(item.getCurrentLocation(),
                                             item.getSpeed(), stepSize));
}


void Simulation::wallReflection(GenericObject &item) {
        if (item.getCurrentLocation()[0] > arena->getWidth() || item.getCurrentLocation()[0] < 0)
            item.setSpeed({-item.getSpeed()[0], item.getSpeed()[1]});
        if (item.getCurrentLocation()[1] > arena->getHeight() || item.getCurrentLocation()[1] < 0)
            item.setSpeed({item.getSpeed()[0], -item.getSpeed()[1]});


}

bool Simulation::checkCollisions(const std::vector<Rectangle>& objects, int i) {
    double side1;
    double side2;
    double dist;
    for (auto &item : objects) {
        if (i < item.getHideTime() && i > item.getRevealTime()) {
            for (auto &item2: objects) {
                if (i < item2.getHideTime() && i > item2.getRevealTime()) {

                    if (item.getName() != item2.getName()) {

                        item.getBSide() < item.getASide() ? side1 = item.getASide() : side1 = item.getBSide();
                        item2.getBSide() < item2.getASide() ? side2 = item2.getASide() : side2 = item2.getBSide();
                        dist = std::sqrt(std::pow(item.getCurrentLocation()[0] - item2.getCurrentLocation()[0], 2) +
                                         std::pow(item.getCurrentLocation()[1] - item2.getCurrentLocation()[1], 2));
                        if (dist < side1 + side2) {
                            collisions.emplace_back(
                                    item.getName() + " " + item2.getName() + " " + std::to_string(i) + "sec " +
                                    std::to_string(item.getCurrentLocation()[0]) + " " +
                                    std::to_string(item.getCurrentLocation()[1]) + " " +
                                    std::to_string(item2.getCurrentLocation()[0]) + " " +
                                    std::to_string(item2.getCurrentLocation()[1]) + " ");
                            if (arena->isEndAfterCollision())
                                return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Simulation::checkCollisions(const std::vector<Ball> &objects, int i) {
    double dist;
    for (auto &item : objects) {
        if (i < item.getHideTime() && i > item.getRevealTime()) {
            for (auto &item2: objects) {
                if (i < item2.getHideTime() && i > item2.getRevealTime()) {

                    if (item.getName() != item2.getName()) {
                        dist = std::sqrt(std::pow(item.getCurrentLocation()[0] - item2.getCurrentLocation()[0], 2) +
                                         std::pow(item.getCurrentLocation()[1] - item2.getCurrentLocation()[1], 2));
                        if (dist < item.getRadius() + item2.getRadius()){
                            collisions.emplace_back(
                                    item.getName() + " " + item2.getName() + " " + std::to_string(i) + "sec " +
                                    std::to_string(item.getCurrentLocation()[0]) + " " +
                                    std::to_string(item.getCurrentLocation()[1]) + " " +
                                    std::to_string(item2.getCurrentLocation()[0]) + " " +
                                    std::to_string(item2.getCurrentLocation()[1]) + " ");
                            if (arena->isEndAfterCollision())
                                return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Simulation::checkCollisions(const std::vector<Square> &objects, int i) {
    double dist;
    for (auto &item : objects) {
        if (i < item.getHideTime() && i > item.getRevealTime()) {
            for (auto &item2: objects) {
                if (i < item2.getHideTime() && i > item2.getRevealTime()) {

                    if (item.getName() != item2.getName()) {
                        dist = std::sqrt(std::pow(item.getCurrentLocation()[0] - item2.getCurrentLocation()[0], 2) +
                                         std::pow(item.getCurrentLocation()[1] - item2.getCurrentLocation()[1], 2));
                        if (dist < item.getASide() + item2.getASide()) {
                            collisions.emplace_back(
                                    item.getName() + " " + item2.getName() + " " + std::to_string(i) + "sec " +
                                    std::to_string(item.getCurrentLocation()[0]) + " " +
                                    std::to_string(item.getCurrentLocation()[1]) + " " +
                                    std::to_string(item2.getCurrentLocation()[0]) + " " +
                                    std::to_string(item2.getCurrentLocation()[1]) + " ");
                            if (arena->isEndAfterCollision())
                                return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

const std::vector<std::string> &Simulation::getCollisions() const {
    return collisions;
}

int Simulation::getVirtualTime() const {
    return virtualTime;
}

const std::unique_ptr<Arena> &Simulation::getArena() const {
    return arena;
}

void Simulation::printDistances(const std::shared_ptr<Loader>& loader, std::ostream &file) {

    if (!loader->getRectangles().empty()) {
        file << loader->getRectangles().size() << std::endl;
        for (auto & item: loader->getRectangles()) {
            file << item.getName() << " " << item.getDistance() << std::endl;
        }
    }
    else if (!loader->getBalls().empty()) {
        file << loader->getBalls().size() << std::endl;
        for (auto & item: loader->getBalls()) {
            file << item.getName() << " " << item.getDistance() << std::endl;
        }
    }
    else if (!loader->getSquares().empty()) {
        file << loader->getSquares().size() << std::endl;
        for (auto & item: loader->getSquares()) {
            file << item.getName() << " " << item.getDistance() << std::endl;
        }
    }


}


