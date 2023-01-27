#include <memory>
#include "Loader.h"
#include "Validator.h"
#include "Simulation.h"
#include <chrono>


/* Writing error message to the output file. */
void write_err(std::ostream &file, std::shared_ptr<Loader> &loader) {

    if (!loader->getErr().empty()) {
        file << "REPORT\n ERROR\n";
        if (loader->getErr().substr(0, 5) == "err w") {
            file << "exit code 3" << std::endl;
            file << loader->getErr() << std::endl;
            exit(3);
        }
        if (loader->getErr().substr(0, 5) == "err i") {
            file << "exit code 4" << std::endl;
            file << loader->getErr() << std::endl;
            exit(4);
        }
    }

}

/* It writes the report to the output file. */
void write_report(std::ostream &file, std::chrono::duration<double> elapsed_seconds, std::unique_ptr<Simulation> &sim, std::shared_ptr<Loader> &loader) {
    file << "REPORT\nOK\n";
    file << sim->getVirtualTime() << std::endl;
    if (sim->getArena()->isEndAfterCollision())
        file << "COLLISION" <<std::endl;
    else file << "TIMEOUT" <<std::endl;
    file << elapsed_seconds.count() * 1000 << " ms" << std::endl;
    file << "COLLISIONS" <<std::endl;
    file << sim->getCollisions().size() << std::endl;
    std::copy(sim->getCollisions().begin(),  sim->getCollisions().end(), std::ostream_iterator<std::string>(file, "\n"));
    if (sim->getArena()->isReportDistance()) {
        file << "DISTANCES" << std::endl;
        sim->printDistances(loader, file);
    }
}


int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "usage:" << std::endl << "./kiv-cpp-sp-01 <input> <output log spec>" << std::endl;
        exit(1);
    }
    std::string input = argv[1];
    std::string flag = argv[2];

    auto loader = std::make_shared<Loader>(input);
    Validator::validateBeforeSimulation(&loader);

    if (flag != "null") {
        if (flag == "cout") {
            std::ostream stream(std::cout.rdbuf());
            write_err(stream, loader);
            auto start = std::chrono::steady_clock::now();
            auto sim = std::make_unique<Simulation>(loader);
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            write_report(stream, elapsed_seconds, sim, loader);
        }
        else {
            std::ofstream stream(flag, std::ios::in);
            if (!stream) {
                std::cout << argv[2] << std::endl;
                std::cout << "output file not found" << std::endl;
                exit(2);
            }
            write_err(stream, loader);
            auto start = std::chrono::steady_clock::now();
            auto sim = std::make_unique<Simulation>(loader);
            auto end = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = end-start;
            write_report(stream, elapsed_seconds, sim, loader);
        }
    }
    else {
        auto sim = std::make_unique<Simulation>(std::move(loader));
    }
    return 0;
}


