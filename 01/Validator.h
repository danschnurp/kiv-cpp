//
// Created by dartix on 28/12/2021.
//

#ifndef CPP_SEMWORK1_VALIDATOR_H
#define CPP_SEMWORK1_VALIDATOR_H


#include "Loader.h"

class Validator {
public:
    /**
     * validates parameters
     * @param loader loader class
     */
    static void validateBeforeSimulation(std::shared_ptr<Loader> *loader);

private:
    static void validateStartLoc(const GenericObject &item, std::shared_ptr<Loader> *loader);

};


#endif //CPP_SEMWORK1_VALIDATOR_H
