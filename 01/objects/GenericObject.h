//
// Created by dartix on 10/13/21.
//

#ifndef CPP_SEMWORK1_GENERICOBJECT_H
#define CPP_SEMWORK1_GENERICOBJECT_H
#include <iostream>
#include <vector>

/**
 * messenger
 */
class GenericObject {

protected:
    std::string name;

    std::vector<float> startLocation;

    std::vector<float> currentLocation;

    std::vector<float> speed;

    // distance for one pseudo time unit
    double stepDistance = 0;

    double distance = 0;

    double revealTime;

    double hideTime;

public:
    GenericObject(std::string name, std::vector<float> startLocation,
                  std::vector<float> currentLocation, std::vector<float> speed, double revealTime,
                  double hideTime);

    virtual const std::string &getName() const;

    virtual const std::vector<float> &getStartLocation() const;

    virtual const std::vector<float> &getCurrentLocation() const;

    virtual const std::vector<float> &getSpeed() const;

    virtual double getRevealTime() const;

    virtual double getHideTime() const;

    virtual double getDistance() const;

    virtual double getStepDistance() const;

    void setSpeed(const std::vector<float> &speed);

    virtual void setStartLocation(const std::vector<float> &vector);

    virtual void setStepDistance(double stepDist);

    virtual void setDistance(double dist);

    virtual void setCurrentLocation(const std::vector<float> &currentLocation);

    friend std::ostream &operator<<(std::ostream &os, const GenericObject &object);

};


#endif //CPP_SEMWORK1_GENERICOBJECT_H
