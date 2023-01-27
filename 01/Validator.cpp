//
// Created by dartix on 28/12/2021.
//

#include "Validator.h"
#include <algorithm>

void Validator::validateBeforeSimulation(std::shared_ptr<Loader> *loader) {
    try {

        auto sq = loader->get()->getSquares();
        auto ba = loader->get()->getBalls();
        auto re = loader->get()->getRectangles();

        std::for_each(sq.begin(), sq.end(), [&](const auto &item) {
            if (std::cref(item).get().getASide() > loader->get()->getArena()->getHeight() ||
                    std::cref(item).get().getASide() > loader->get()->getArena()->getWidth()) {
                throw std::string{std::cref(item).get().getName() + " is bigger than arena "};
            }
            validateStartLoc((const GenericObject &) item, loader);
        });

        std::for_each(ba.begin(), ba.end(), [&](const auto &item) {
            if (std::cref(item).get().getRadius() * 2 > loader->get()->getArena()->getHeight() ||
                std::cref(item).get().getRadius() * 2 > loader->get()->getArena()->getWidth()) {
                throw std::string{std::cref(item).get().getName() + " is bigger than arena "};
            }
            validateStartLoc((const GenericObject &) item, loader);
        });

        std::for_each(re.begin(), re.end(), [&](const auto &item) {
            if (std::cref(item).get().getASide() > loader->get()->getArena()->getHeight() ||
                std::cref(item).get().getASide() > loader->get()->getArena()->getWidth() ||
                std::cref(item).get().getBSide() > loader->get()->getArena()->getHeight() ||
                std::cref(item).get().getBSide() > loader->get()->getArena()->getWidth()) {
                throw std::string{std::cref(item).get().getName() + " is bigger than arena "};
            }
            validateStartLoc((const GenericObject &) item, loader);
        });

    }
    catch (std::string &err) {
        loader->get()->setErr("err in validation: " + err);
        return;
    }
}

void Validator::validateStartLoc(const GenericObject &item, std::shared_ptr<Loader> *loader) {
    if (std::cref(item).get().getStartLocation()[0] > loader->get()->getArena()->getHeight() ||
        std::cref(item).get().getStartLocation()[0] > loader->get()->getArena()->getWidth() ||
        std::cref(item).get().getStartLocation()[1] > loader->get()->getArena()->getHeight() ||
        std::cref(item).get().getStartLocation()[1] > loader->get()->getArena()->getWidth()) {
        throw std::string{std::cref(item).get().getName() + " is out of arena "};
    }

}

