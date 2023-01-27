//
// Created by dartix on 1/9/22.
//

#include "Pair.h"


Pair::Pair(std::string first, std::string second) : first(std::move(first)), second(std::move(second)) {}

Pair::Pair(double f, double s) : f(f), s(s) {}

Pair::Pair(std::string first, double s) : first(std::move(first)), s(s) {}

Pair::Pair(double f, std::string second) : first(std::move(second)), s(f) {}

const std::string &Pair::getFirst() const {
    return first;
}

const std::string &Pair::getSecond() const {
    return second;
}

double Pair::getF() const {
    return f;
}

double Pair::getS() const {
    return s;
}

Pair::Pair() {}

bool Pair::operator==(const Pair &rhs) const {
    return first == rhs.first &&
           second == rhs.second &&
           f == rhs.f &&
           s == rhs.s;
}

bool Pair::operator!=(const Pair &rhs) const {
    return !(rhs == *this);
}

bool operator<(const Pair &lhs, const Pair &rhs) {
    if (lhs.first < rhs.first)
        return true;
    if (rhs.first < lhs.first)
        return false;
    if (lhs.second < rhs.second)
        return true;
    if (rhs.second < lhs.second)
        return false;
    if (lhs.f < rhs.f)
        return true;
    if (rhs.f < lhs.f)
        return false;
    return lhs.s < rhs.s;
}

bool operator>(const Pair &lhs, const Pair &rhs) {
    return rhs < lhs;
}

bool operator<=(const Pair &lhs, const Pair &rhs) {
    return !(rhs < lhs);
}

bool operator>=(const Pair &lhs, const Pair &rhs) {
    return !(lhs < rhs);
}

std::ostream &operator<<(std::ostream &os, const Pair &pair) {
    os << (!pair.first.empty() ? " first: " + pair.first : "")
    << (!pair.second.empty() ? " second: " + pair.second : "") <<
    (pair.f != INT32_MAX ? " f: " + std::to_string(pair.f) : "") <<
    (pair.s != INT32_MAX ?  " s: "+ std::to_string(pair.s) : "");
    return os;
}


