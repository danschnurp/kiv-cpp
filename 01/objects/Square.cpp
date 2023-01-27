//
// Created by dartix on 10/13/21.
//

#include "Square.h"

Square::Square(const std::string &name, const std::vector<float> &startLocation,
               const std::vector<float> &currentLocation, const std::vector<float> &speed, double revealTime,
               double hideTime, double aSide) : GenericObject(name, startLocation, currentLocation, speed, revealTime,
                                                              hideTime), aSide(aSide) {}

double Square::getASide() const {
    return aSide;
}

std::ostream &operator<<(std::ostream &os, const Square &square) {
    os << static_cast<const GenericObject &>(square) << " aSide: " << square.aSide;
    return os;
}

const std::string &Square::getName() const {
    return GenericObject::getName();
}

const std::vector<float> &Square::getStartLocation() const {
    return GenericObject::getStartLocation();
}

const std::vector<float> &Square::getCurrentLocation() const {
    return GenericObject::getCurrentLocation();
}

const std::vector<float> &Square::getSpeed() const {
    return GenericObject::getSpeed();
}

double Square::getRevealTime() const {
    return GenericObject::getRevealTime();
}

double Square::getHideTime() const {
    return GenericObject::getHideTime();
}

double Square::getDistance() const {
    return GenericObject::getDistance();
}

void Square::setDistance(double dist) {
    GenericObject::setDistance(dist);
}

void Square::setCurrentLocation(const std::vector<float> &currentLocation) {
    GenericObject::setCurrentLocation(currentLocation);
}

double Square::getStepDistance() const {
    return GenericObject::getStepDistance();
}

void Square::setStepDistance(double stepDistance) {
    GenericObject::setStepDistance(stepDistance);
}

void Square::setStartLocation(const std::vector<float> &startLocation) {
    GenericObject::setStartLocation(startLocation);
}
