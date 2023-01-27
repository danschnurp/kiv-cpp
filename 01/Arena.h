//
// Created by dartix on 30.09.21.
//

#ifndef CPP_SEMWORK1_ARENA_H
#define CPP_SEMWORK1_ARENA_H


#include <ostream>

/**
 * messenger
 */
class Arena {
private:
    float width;
    float height;
    // size of one step
    float stepLen;
    int maxSteps;
    bool reportDistance = false;
    bool endAfterCollision = false;
public:
    friend std::ostream &operator<<(std::ostream &os, const Arena &arena);

    Arena(float width, float height, float stepLen, int maxSteps);

    float getWidth() const;

    float getHeight() const;

    float getStepLen() const;

    int getMaxSteps() const;

    void setReportDistance(bool reportDistance);

    void setEndAfterCollision(bool endAfterCollision);

    bool isReportDistance() const;

    bool isEndAfterCollision() const;

    };


#endif //CPP_SEMWORK1_ARENA_H
