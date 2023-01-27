//
// Created by dartix on 10/13/21.
//

#include "GenericObject.h"

#include <utility>

GenericObject::GenericObject(std::string name, std::vector<float> startLocation,
                             std::vector<float> currentLocation, std::vector<float> speed,
                             double revealTime, double hideTime) : name(std::move(name)), startLocation(std::move(startLocation)),
                                                                   currentLocation(std::move(currentLocation)), speed(std::move(speed)),
                                                                   revealTime(revealTime), hideTime(hideTime) {}

const std::string &GenericObject::getName() const {
    return name;
}

const std::vector<float> &GenericObject::getStartLocation() const {
    return startLocation;
}

const std::vector<float> &GenericObject::getCurrentLocation() const {
    return currentLocation;
}

const std::vector<float> &GenericObject::getSpeed() const {
    return speed;
}

double GenericObject::getRevealTime() const {
    return revealTime;
}

double GenericObject::getHideTime() const {
    return hideTime;
}

void GenericObject::setCurrentLocation(const std::vector<float> &currentLoc) {
    GenericObject::currentLocation = currentLoc;
}

std::ostream &operator<<(std::ostream &os, const GenericObject &object) {
    os << "name: " << object.name << " startLocation: " << object.startLocation[0]<< "," << object.startLocation[1] << " currentLocation: "
       << object.currentLocation[0]<< "," << object.currentLocation[1] << " speed: " <<
        object.speed[0]<< "," << object.speed[1] << " revealTime: " << object.revealTime << " hideTime: "
       << object.hideTime;
    return os;
}

double GenericObject::getDistance() const {
    return distance;
}

void GenericObject::setDistance(double dist) {
    GenericObject::distance = dist;
}

double GenericObject::getStepDistance() const {
    return stepDistance;
}

void GenericObject::setStepDistance(double stepDist) {
    GenericObject::stepDistance = stepDist;
}

void GenericObject::setStartLocation(const std::vector<float> &vector) {
    GenericObject::startLocation = vector;
}

void GenericObject::setSpeed(const std::vector<float> &speed) {
    GenericObject::speed = speed;
}


