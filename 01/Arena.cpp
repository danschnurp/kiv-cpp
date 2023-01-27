//
// Created by dartix on 30.09.21.
//

#include "Arena.h"


/**
 * It's a constructor for the Arena class
 *
 * @param width The width of the arena.
 * @param height The height of the arena.
 * @param stepLen The length of a step in the arena.
 * @param maxSteps The maximum number of steps the agent can take before the episode is terminated.
 */
Arena::Arena(float width, float height, float stepLen, int maxSteps)
        : width(width), height(height), stepLen(stepLen), maxSteps(maxSteps) {}

/**
 * `getWidth` returns the width of the arena
 *
 * @return The width of the arena.
 */
float Arena::getWidth() const {
    return width;
}

/**
 * `float Arena::getHeight() const`
 *
 * This function returns the height of the arena
 *
 * @return The height of the arena.
 */
float Arena::getHeight() const {
    return height;
}

/**
 *
 *
 * @return The stepLen variable is being returned.
 */
float Arena::getStepLen() const {
    return stepLen;
}

/**
 *
 *
 * @return The maxSteps variable is being returned.
 */
int Arena::getMaxSteps() const {
    return maxSteps;
}

/**
 *
 *
 * @return The value of the reportDistance variable.
 */
bool Arena::isReportDistance() const {
    return reportDistance;
}

/**
 *
 *
 * @return The value of the private member variable endAfterCollision.
 */
bool Arena::isEndAfterCollision() const {
    return endAfterCollision;
}

/**
 *
 *
 * @param reportDistance If true, the arena will report the distance between the robot and the nearest obstacle.
 */
void Arena::setReportDistance(bool reportDistance) {
    Arena::reportDistance = reportDistance;
}

/**
 * This function sets the value of the private member variable `endAfterCollision` to the value of the parameter
 * `endAfterCollision`
 *
 * @param endAfterCollision If true, the game will end after a collision.
 */
void Arena::setEndAfterCollision(bool endAfterCollision) {
    Arena::endAfterCollision = endAfterCollision;
}

/**
 * It takes an Arena object and an ostream object, and it prints the
 * Arena object to the ostream object
 *
 * @return The ostream object is being returned.
 */
std::ostream &operator<<(std::ostream &os, const Arena &arena) {
    os << "width: " << arena.width << " height: " << arena.height << " stepLen: " << arena.stepLen << " maxSteps: "
       << arena.maxSteps << " reportDistance: " << arena.reportDistance << " endAfterCollision: "
       << arena.endAfterCollision;
    return os;
}

