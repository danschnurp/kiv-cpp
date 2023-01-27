//
// Created by dartix on 1/9/22.
//

#ifndef KIV_CPP_SP_02_ROW_H
#define KIV_CPP_SP_02_ROW_H


#include <vector>
#include <string>
#include <variant>
#include <ostream>
#include "Pair.h"

class Row {

public:


    Row(std::variant<int, double, std::string, Pair> key, std::vector<int> dataInt, std::vector<double> dataDouble,
        std::vector<std::string> dataStr, std::vector<Pair> dataPair);


    Row(int keyInt, std::vector<int> dataInt, std::vector<double> dataDouble,
        std::vector<std::string> dataStr, std::vector<Pair> dataPair);

    Row(Pair keyPair, std::vector<int> dataInt, std::vector<double> dataDouble,
        std::vector<std::string> dataStr, std::vector<Pair> dataPair);

    Row(double keyDouble, std::vector<int> dataInt, std::vector<double> dataDouble,
        std::vector<std::string> dataStr, std::vector<Pair> dataPair);

    Row(std::string keyStr, std::vector<int> dataInt, std::vector<double> dataDouble,
        std::vector<std::string> dataStr, std::vector<Pair> dataPair);

    int getKeyInt() const;

    double getKeyDouble() const;

    const std::string &getKeyStr() const;

    const Pair &getKeyPair() const;

    const std::vector<int> & getDataInt() const;

    const std::vector<double> &getDataDouble() const;

    const std::vector<std::string> &getDataStr() const;

    const std::vector<Pair> &getDataPair() const;

    bool equality(std::variant<int, double, std::string, Pair> key);

    bool equality(int key) const;

    bool equality(double key) const;

    bool equality(const std::string& key);

    bool equality(const Pair& key);

    double greater(std::variant<int, double, std::string, Pair> key) const;

    double greater(double key) const;

    double greater(Pair& key) const;

    double greater(const std::string&  key) const;

    double lesser(std::variant<int, double, std::string, Pair> key) const;

    double lesser(Pair& key) const;

    double lesser(const std::string&  key) const;

    double lesser(double key) const;

    double getAverage() const;

    friend std::ostream &operator<<(std::ostream &os, const Row &row);

private:

    int keyInt = INT32_MAX;

    double keyDouble = INT32_MAX;

    std::string keyStr = "";

    Pair keyPair;

    std::vector<int> dataInt;

    std::vector<double> dataDouble;

    std::vector<std::string> dataStr;

    std::vector<Pair> dataPair;


};


#endif //KIV_CPP_SP_02_ROW_H
