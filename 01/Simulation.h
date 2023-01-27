//
// Created by dartix on 01/01/2022.
//

#ifndef CPP_SEMWORK1_SIMULATION_H
#define CPP_SEMWORK1_SIMULATION_H

#include <cmath>
#include "Loader.h"

/**
 * makes discrete simulation
 */
class Simulation {

private:
    std::unique_ptr<Arena> arena;

    std::vector<std::string> collisions;

    int virtualTime;

    bool checkCollisions(const std::vector<Rectangle>& objects, int i);

    bool checkCollisions(const std::vector<Ball>& objects, int i);

    bool checkCollisions(const std::vector<Square>& objects, int i);

    void moveObj(GenericObject &item);

    void wallReflection(GenericObject &item);

public:

    /**
     * constructor
     * @param loader loader class
     */
    explicit Simulation(std::shared_ptr<Loader> loader);

    /**
     * getter
     * @return vector of collisions
     */
    const std::vector<std::string> &getCollisions() const;

    /**
     *
     * @param loader loader class
     * @param file destination
     */
    void printDistances(const std::shared_ptr<Loader>& loader, std::ostream &file) ;

    int getVirtualTime() const;

    const std::unique_ptr<Arena> &getArena() const;


};


#endif //CPP_SEMWORK1_SIMULATION_H
