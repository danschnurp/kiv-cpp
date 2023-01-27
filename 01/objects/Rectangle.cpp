//
// Created by dartix on 10/13/21.
//

#include "Rectangle.h"

Rectangle::Rectangle(const std::string &name, const std::vector<float> &startLocation,
                     const std::vector<float> &currentLocation, const std::vector<float> &speed, double revealTime,
                     double hideTime, double aSide, double bSide) : Square(name, startLocation, currentLocation, speed,
                                                                           revealTime, hideTime, aSide), bSide(bSide) {}

double Rectangle::getBSide() const {
    return bSide;
}

std::ostream &operator<<(std::ostream &os, const Rectangle &rectangle) {
    os << static_cast<const Square &>(rectangle) << " bSide: " << rectangle.bSide;
    return os;
}

double Rectangle::getASide() const {
    return Square::getASide();
}

const std::string &Rectangle::getName() const {
    return Square::getName();
}

const std::vector<float> &Rectangle::getStartLocation() const {
    return Square::getStartLocation();
}

const std::vector<float> &Rectangle::getCurrentLocation() const {
    return Square::getCurrentLocation();
}

const std::vector<float> &Rectangle::getSpeed() const {
    return Square::getSpeed();
}

double Rectangle::getRevealTime() const {
    return Square::getRevealTime();
}

double Rectangle::getHideTime() const {
    return Square::getHideTime();
}

double Rectangle::getDistance() const {
    return Square::getDistance();
}

void Rectangle::setDistance(double dist) {
    Square::setDistance(dist);
}

void Rectangle::setCurrentLocation(const std::vector<float> &currentLocation) {
    Square::setCurrentLocation(currentLocation);
}

double Rectangle::getStepDistance() const {
    return Square::getStepDistance();
}

void Rectangle::setStepDistance(double stepDistance) {
    Square::setStepDistance(stepDistance);
}

void Rectangle::setStartLocation(const std::vector<float> &startLocation) {
    Square::setStartLocation(startLocation);
}
