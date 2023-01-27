//
// Created by dartix on 10/13/21.
//

#ifndef CPP_SEMWORK1_BALL_H
#define CPP_SEMWORK1_BALL_H

#include <ostream>
#include "GenericObject.h"


class Ball : public GenericObject {
private:
    float radius;


public:
    Ball(const std::string &name, const std::vector<float> &startLocation, const std::vector<float> &currentLocation,
         const std::vector<float> &speed, double revealTime, double hideTime, float radius);

    float getRadius() const;

    const std::string &getName() const override;

    const std::vector<float> &getStartLocation() const override;

    const std::vector<float> &getCurrentLocation() const override;

    const std::vector<float> &getSpeed() const override;

    double getRevealTime() const override;

    double getHideTime() const override;

    double getDistance() const override;

    double getStepDistance() const override;

    void setStepDistance(double stepDistance) override;

    void setStartLocation(const std::vector<float> &startLocation) override;

    void setDistance(double dist) override;

    void setCurrentLocation(const std::vector<float> &currentLocation) override;

    friend std::ostream &operator<<(std::ostream &os, const Ball &ball);


};


#endif //CPP_SEMWORK1_BALL_H
