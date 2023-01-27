//
// Created by dartix on 1/9/22.
//

#include "Row.h"

#include <utility>
#include <iterator>

const std::vector<int> & Row::getDataInt() const {
    return dataInt;
}


const std::vector<double> &Row::getDataDouble() const {
    return dataDouble;
}

const std::vector<std::string> &Row::getDataStr() const {
    return dataStr;
}

int Row::getKeyInt() const {
    return keyInt;
}

double Row::getKeyDouble() const {
    return keyDouble;
}

const std::string &Row::getKeyStr() const {
    return keyStr;
}

const std::vector<Pair> &Row::getDataPair() const {
    return dataPair;
}

Row::Row(int keyInt, std::vector<int> dataInt, std::vector<double> dataDouble,
         std::vector<std::string> dataStr, std::vector<Pair> dataPair) : keyInt(keyInt), dataInt(std::move(dataInt)),
                                                                                       dataDouble(std::move(dataDouble)),
                                                                                       dataStr(std::move(dataStr)),
                                                                                       dataPair(std::move(dataPair)) {}

Row::Row(Pair keyPair, std::vector<int> dataInt, std::vector<double> dataDouble,
         std::vector<std::string> dataStr, std::vector<Pair> dataPair) : keyPair(std::move(keyPair)),
                                                                                       dataInt(std::move(dataInt)),
                                                                                       dataDouble(std::move(dataDouble)),
                                                                                       dataStr(std::move(dataStr)),
                                                                                       dataPair(std::move(dataPair)) {}

Row::Row(double keyDouble, std::vector<int> dataInt, std::vector<double> dataDouble,
         std::vector<std::string> dataStr, std::vector<Pair> dataPair) : keyDouble(keyDouble),
                                                                                       dataInt(std::move(dataInt)),
                                                                                       dataDouble(std::move(dataDouble)),
                                                                                       dataStr(std::move(dataStr)),
                                                                                       dataPair(std::move(dataPair)) {}

Row::Row(std::string keyStr, std::vector<int> dataInt, std::vector<double> dataDouble,
         std::vector<std::string> dataStr, std::vector<Pair> dataPair) : keyStr(std::move(keyStr)), dataInt(std::move(dataInt)),
                                                                                       dataDouble(std::move(dataDouble)),
                                                                                       dataStr(std::move(dataStr)),
                                                                                       dataPair(std::move(dataPair)) {}

const Pair &Row::getKeyPair() const {
    return keyPair;
}

bool Row::equality(int key) const {
    return keyInt != INT32_MAX && keyInt == key;
}

bool Row::equality(double key) const {
    return keyDouble != INT32_MAX && keyDouble == key;
}

bool Row::equality(const std::string& key) {
    return keyStr == key;
}

bool Row::equality(const Pair& key) {
    return keyPair == key;
}

double Row::greater(double key) const {
    if (keyDouble != INT32_MAX && keyDouble > key)
        return keyDouble;
    else if (keyInt != INT32_MAX && keyInt > key)
        return keyInt;
    return INT32_MAX;
}


double Row::lesser(double key) const {
    if (keyDouble != INT32_MAX && keyDouble < key)
        return keyDouble;
    else if (keyInt != INT32_MAX && keyInt < key)
        return keyInt;
    return INT32_MAX;
}

double Row::greater(Pair &key) const {
    return INT32_MAX;
}

double Row::lesser(const std::string &key) const {
    return INT32_MAX;
}

double Row::lesser(Pair &key) const {
    return INT32_MAX;
}

double Row::greater(const std::string &key) const {
    return INT32_MAX;
}

double Row::getAverage() const {
    double sum1 = 0;
    for (const auto &item : dataInt)
        sum1 += item;
    double sum2 = 0;
    for (const auto &item : dataDouble)
        sum2 += item;

    return (sum1 + sum2) / static_cast<double>(dataDouble.size() + dataInt.size());
}

Row::Row(std::variant<int, double, std::string, Pair> key, std::vector<int> dataInt, std::vector<double> dataDouble,
         std::vector<std::string> dataStr, std::vector<Pair> dataPair) : dataInt(std::move(dataInt)),
                                                                         dataDouble(std::move(dataDouble)),
                                                                         dataStr(std::move(dataStr)),
                                                                         dataPair(std::move(dataPair)) {

    std::visit([this](auto &&arg) {
        if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, int>)
            keyInt = arg;
        else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, Pair>)
            keyPair = arg;
        else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, double>)
            keyDouble = arg;
        else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::string>)
            keyStr = arg;
        else
            return false;

    }, key);


}

bool Row::equality(std::variant<int, double, std::string, Pair> key) {
    return std::visit([this](auto &&arg) {
        if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, int>)
            return keyInt != INT32_MAX && keyInt == arg;
        else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, Pair>)
            return keyPair == arg;
        else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, double>)
            return keyDouble != INT32_MAX && keyDouble == arg;
        else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::string>)
            return keyStr == arg;
        else
            return false;
    }, key);

}

double Row::greater(std::variant<int, double, std::string, Pair> key) const {
    int i = INT32_MAX;
    double d = INT32_MAX;

    std::visit([&i, &d](auto &&arg) {
        if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, int>) {
            i = arg;
        }
        else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, double>) {
            d = arg;
        }
        else
            return;
    }, key);
    if (i != INT32_MAX) return greater(i);
    if (d != INT32_MAX) return greater(d);

    return INT32_MAX;
}

double Row::lesser(std::variant<int, double, std::string, Pair> key) const {
    int i = INT32_MAX;
    double d = INT32_MAX;

    std::visit([&i, &d](auto &&arg) {
        if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, int>) {
            i = arg;
        }
        else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, double>) {
            d = arg;
        }
        else
            return;
    }, key);
    if (i != INT32_MAX) return lesser(i);
    if (d != INT32_MAX) return lesser(d);

    return INT32_MAX;
}

std::ostream &operator<<(std::ostream &os, const Row &row) {
    os << (row.keyInt != INT32_MAX ? std::to_string(row.keyInt) : "")
    << (row.keyDouble != INT32_MAX ? std::to_string(row.keyDouble) : "")<< row.keyStr
       << row.keyPair << " - ";
    for (int i= 0; i < row.dataInt.size(); i++) {
        if (i + 1 == row.dataInt.size())
            os << " " << row.dataInt[i];
        else    os << " " << row.dataInt[i] << ",";
    }
    for (int i= 0; i < row.dataDouble.size(); i++) {
        if (i + 1 == row.dataDouble.size())
            os << " " << row.dataDouble[i];
        else    os << " " << row.dataDouble[i] << ",";
    }
    for (int i= 0; i < row.dataStr.size(); i++) {
        if (i + 1 == row.dataStr.size())
            os << " " << row.dataStr[i];
        else    os << " " << row.dataStr[i] << ",";
    }
    for (int i= 0; i < row.dataPair.size(); i++) {
        if (i + 1 == row.dataPair.size())
            os << " " << "[" << row.dataPair[i] << "]";
        else
        os << " " << "[" << row.dataPair[i] << "],";
    }



    return os;
}




