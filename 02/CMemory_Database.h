//
// Created by dartix on 1/6/22.
//

#ifndef KIV_CPP_SP_02_CMEMORY_DATABASE_H
#define KIV_CPP_SP_02_CMEMORY_DATABASE_H

#include <vector>
#include <variant>
#include <tuple>
#include "specialized_rows/Row.h"

/**
 * basic concept for the control of data types
 * @tparam T eg. int
 * @tparam U eg. double, class Pair...
 */
template<typename ... U>
concept IsAnyOf = (std::same_as<U, U> || ...);

/**
 * My representation of CMemory database with api defined as template functions
 * @author Daniel Schnurpfeil
 */
class CMemory_Database
{

private:

    /**
     * representation of memory only database table
     */
    std::vector<Row> table;
public:

    /**
     * getter
     * @return table
     */
    std::vector<Row> &getTable();

    enum class db_operation
    {
        Equals,
        Greater_Than,
        Less_Than
    };

    /**
     * inserts row to the database table
     * currently supports data types of attributes defined in class specialized_rows/Row.h
     * @tparam key_type int, double, std::string, class Pair in specialized_rows/Pair.h
     * @tparam Args vectors of: int, double, std::string, class Pair in specialized_rows/Pair.h
     * @param key key expression
     * @param args data (all four vectors (int, double, std::string, class Pair)) can be empty
     * @return bool true if ok false of not ok
     */
    template<typename key_type, typename ... Args>
    auto Insert(key_type key, Args&& ... args);

    /**
     * deletes row from the database table
     * currently supports data types of attributes defined in class specialized_rows/Row.h
     * @tparam key_type int, double, std::string, class Pair in specialized_rows/Pair.h
     * @param key key expression
     * @return bool true if ok false of not ok
     */
    template<typename key_type>
    auto  Delete(key_type key);

    /**
     * finds row(s) from the database table based on key
     * currently supports data types of attributes defined in class specialized_rows/Row.h
     * @tparam key_type int, double, std::string, class Pair in specialized_rows/Pair.h
     * @param key key expression
     * @param op enum class db_operation
     * @return if db_operation::Equals returns matched or empty vector of rows
     *         if db_operation::Greater_Than returns greater rows (with keys double or int) or empty vector of rows
     *         if db_operation::Less_Than returns lesser rows (with keys double or int) or empty vector of rows
     */
    template<typename key_type>
    std::vector<Row> Search_Key(key_type key, db_operation op);

    /**
     * finds value in db...
     * @tparam functor_type function validated by concept
     * @param func function validated by concept
     * @return bool true if ok false of not ok
     */
    template<class functor_type> requires IsAnyOf<int, double, std::string, Pair>
    auto Find_Value(functor_type func);

    /**
     * counts average of db values
     * @return average
     */
    double Average();

    /**
     * counts min of db values
     * @return tuple
     */
    auto Min();

    /**
     * counts max of db values
     * @return tuple
     */
    auto Max();

    template<typename key_type>
    auto Min(key_type key);

    template<typename key_type>
    auto Max(key_type key);

    /**
     * counts average of db values
     * @tparam key_type int, double, std::string, class Pair in specialized_rows/Pair.h
     * @param key key expression
     * @return average or throws err if key not found
     */
    template<typename key_type>
    double Average(key_type key);


};
////////////////////////////////////////////////
/// IMPLEMENTED METHODS START
////////////////////////////////

template<typename key_type, typename... Args>
auto CMemory_Database::Insert(key_type key, Args &&... args) {
    if (!Search_Key(key, db_operation::Equals).empty())
        return false;
    table.emplace_back(Row(key, std::forward<Args>(args)...));
    return true;
}

template<typename key_type>
std::vector<Row> CMemory_Database::Search_Key(key_type key, CMemory_Database::db_operation op) {
    std::vector<Row> result;
    if (op == db_operation::Equals) {
        for (auto &item: table) {
            if (item.equality(key)) {
                result.push_back(item);
                return result;
            }
        }
    }
    else if (op == db_operation::Greater_Than) {
        for (auto &item: table) {
            if (item.greater(key) != INT32_MAX) {
                result.push_back(item);
            }
        }
    }
    else if (op == db_operation::Less_Than) {
        for (auto &item: table) {
            if (item.lesser(key) != INT32_MAX) {
                result.push_back(item);
            }
        }
    }
    return result;
}

template<typename key_type>
auto CMemory_Database::Delete(key_type key) {
    for (auto it = table.begin(); it != table.end();) {
        if (it->equality(key)) {
            table.erase(it);
            return true;
        } else {
            ++it;
        }
    }
    return false;
}


template<class functor_type> requires IsAnyOf<int, double, std::string, Pair>
auto CMemory_Database::Find_Value(functor_type func) {
    return func;
}

std::vector<Row> &CMemory_Database::getTable() {
    return table;
}

double CMemory_Database::Average() {
    double sum =  0;
    double counter = 0;
    for (const auto &item : table) {
        for (const auto &item1 : item.getDataInt()) {
            counter++;
            sum += item1;
        }
        for (const auto &item1 : item.getDataDouble()) {
            counter++;
            sum += item1;
        }
    }
    if (counter > 0)
        return sum / counter;
    return INT32_MAX;
}

template<typename key_type>
double CMemory_Database::Average(key_type key) {
    std::vector<Row> result = Search_Key(key, db_operation::Equals);
    if (result.empty())
        throw std::string {"key not fond"};
    return result[0].getAverage();

}

auto CMemory_Database::Min() {
    std::string resultStr;
    int resultInt = INT32_MAX;
    double  resultDouble = INT32_MAX;
    Pair resultPair;
    for (const auto &item : table) {
        for (auto &str : item.getDataStr()) {
            if (resultStr > str) {
                resultStr = str;
            }
        }
        for (auto &item1 : item.getDataInt()) {
            if (resultInt > item1) {
                resultInt = item1;
            }
        }
        for (auto &item1 : item.getDataDouble()) {
            if (resultDouble > item1) {
                resultDouble = item1;
            }
        }
        for (auto &item1 : item.getDataPair()) {
            if (resultPair > item1) {
                resultPair = item1;
            }
        }
    }
    return std::make_tuple(resultStr, resultInt, resultDouble, resultPair);
}

auto CMemory_Database::Max() {
    std::string resultStr;
    int resultInt = -INT32_MAX;
    double  resultDouble = -INT32_MAX;
    Pair resultPair;
    for (const auto &item : table) {
        for (const auto &str : item.getDataStr()) {
            if (resultStr < str) {
                resultStr = str;
            }
        }
        for (const auto &item1 : item.getDataInt()) {
            if (resultInt < item1) {
                resultInt = item1;
            }
        }
        for (const auto &item1 : item.getDataDouble()) {
            if (resultDouble < item1) {
                resultDouble = item1;
            }
        }
        for (const auto &item1 : item.getDataPair()) {
            if (resultPair < item1) {
                resultPair = item1;
            }
        }
    }
    return std::make_tuple(resultStr, resultInt, resultDouble, resultPair);
}

template<typename key_type>
auto CMemory_Database::Max(key_type key) {
    std::vector<Row> result = Search_Key(key, db_operation::Equals);
    if (result.empty())
        throw std::string {"key not fond"};

    std::string resultStr;
    int resultInt;
    double  resultDouble;
    Pair resultPair;

        for (const auto &str : result[0].getDataStr()) {
            if (resultStr < str) {
                resultStr = str;
            }
        }
        for (const auto &item1 : result[0].getDataInt()) {
            if (resultInt < item1) {
                resultInt = item1;
            }
        }
        for (const auto &item1 : result[0].getDataDouble()) {
            if (resultDouble < item1) {
                resultDouble = item1;
            }
        }
        for (const auto &item1 : result[0].getDataPair()) {
            if (resultPair < item1) {
                resultPair = item1;
            }
        }

    return std::make_tuple(resultStr, resultInt, resultDouble, resultPair);

}

template<typename key_type>
auto CMemory_Database::Min(key_type key) {
    std::vector<Row> result = Search_Key(key, db_operation::Equals);
    if (result.empty())
        throw std::string {"key not fond"};

    std::string resultStr;
    int resultInt;
    double  resultDouble;
    Pair resultPair;

    for (const auto &str : result[0].getDataStr()) {
        if (resultStr > str) {
            resultStr = str;
        }
    }
    for (const auto &item1 : result[0].getDataInt()) {
        if (resultInt > item1) {
            resultInt = item1;
        }
    }
    for (const auto &item1 : result[0].getDataDouble()) {
        if (resultDouble > item1) {
            resultDouble = item1;
        }
    }
    for (const auto &item1 : result[0].getDataPair()) {
        if (resultPair > item1) {
            resultPair = item1;
        }
    }
    return std::make_tuple(resultStr, resultInt, resultDouble, resultPair);
}

////////////////////////////////
/// IMPLEMENTED METHODS END
////////////////////////////////////////////////

#endif //KIV_CPP_SP_02_CMEMORY_DATABASE_H
