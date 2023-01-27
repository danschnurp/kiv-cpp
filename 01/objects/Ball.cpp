//
// Created by dartix on 10/13/21.
//

#include "Ball.h"

Ball::Ball(const std::string &name, const std::vector<float> &startLocation, const std::vector<float> &currentLocation,
           const std::vector<float> &speed, double revealTime, double hideTime, float radius) : GenericObject(name,
                                                                                                              startLocation,
                                                                                                              currentLocation,
                                                                                                              speed,
                                                                                                              revealTime,
                                                                                                              hideTime),
                                                                                                radius(radius) {}

float Ball::getRadius() const {
    return radius;
}

std::ostream &operator<<(std::ostream &os, const Ball &ball) {
    os << static_cast<const GenericObject &>(ball) << " radius: " << ball.radius;
    return os;
}

const std::string &Ball::getName() const {
    return GenericObject::getName();
}

const std::vector<float> &Ball::getStartLocation() const {
    return GenericObject::getStartLocation();
}

const std::vector<float> &Ball::getCurrentLocation() const {
    return GenericObject::getCurrentLocation();
}

const std::vector<float> &Ball::getSpeed() const {
    return GenericObject::getSpeed();
}

double Ball::getRevealTime() const {
    return GenericObject::getRevealTime();
}

double Ball::getHideTime() const {
    return GenericObject::getHideTime();
}

double Ball::getDistance() const {
    return GenericObject::getDistance();
}

void Ball::setDistance(double dist) {
    GenericObject::setDistance(dist);
}

void Ball::setCurrentLocation(const std::vector<float> &currentLocation) {
    GenericObject::setCurrentLocation(currentLocation);
}

double Ball::getStepDistance() const {
    return GenericObject::getStepDistance();
}

void Ball::setStepDistance(double stepDistance) {
    GenericObject::setStepDistance(stepDistance);
}

void Ball::setStartLocation(const std::vector<float> &startLocation) {
    GenericObject::setStartLocation(startLocation);
}
