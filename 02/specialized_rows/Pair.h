//
// Created by dartix on 1/9/22.
//

#ifndef KIV_CPP_SP_02_PAIR_H
#define KIV_CPP_SP_02_PAIR_H


#include <string>
#include <ostream>

class Pair {
    std::string first;
    std::string second;
    double f = INT32_MAX;
    double s = INT32_MAX;

public:

    Pair();

    Pair(std::string first, std::string second);

    Pair(double f, double s);

    Pair(std::string first, double s);

    Pair(double f, std::string second);

    const std::string &getFirst() const;

    const std::string &getSecond() const;

    double getF() const;

    double getS() const;

    bool operator==(const Pair &rhs) const;

    bool operator!=(const Pair &rhs) const;

    friend bool operator<(const Pair &lhs, const Pair &rhs);

    friend bool operator>(const Pair &lhs, const Pair &rhs);

    friend bool operator<=(const Pair &lhs, const Pair &rhs);

    friend bool operator>=(const Pair &lhs, const Pair &rhs);

    friend std::ostream &operator<<(std::ostream &os, const Pair &pair);

};


#endif //KIV_CPP_SP_02_PAIR_H
