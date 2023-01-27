//
// Created by dartix on 10/13/21.
//

#ifndef CPP_SEMWORK1_SQUARE_H
#define CPP_SEMWORK1_SQUARE_H

#include <ostream>
#include "GenericObject.h"

class Square: public GenericObject{
protected:
    double aSide;

public:

    Square(const std::string &name, const std::vector<float> &startLocation, const std::vector<float> &currentLocation,
           const std::vector<float> &speed, double revealTime, double hideTime, double aSide);

    virtual double getASide() const;

    friend std::ostream &operator<<(std::ostream &os, const Square &square);

    const std::string &getName() const override;

    const std::vector<float> &getStartLocation() const override;

    const std::vector<float> &getCurrentLocation() const override;

    const std::vector<float> &getSpeed() const override;

    double getRevealTime() const override;

    double getHideTime() const override;

    double getDistance() const override;

    double getStepDistance() const override;

    void setStartLocation(const std::vector<float> &startLocation) override;

    void setStepDistance(double stepDistance) override;

    void setDistance(double dist) override;

    void setCurrentLocation(const std::vector<float> &currentLocation) override;


};


#endif //CPP_SEMWORK1_SQUARE_H
