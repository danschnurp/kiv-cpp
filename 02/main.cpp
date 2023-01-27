//
// Created by dartix on 1/6/22.
//

#include "CMemory_Database.h"
#include <memory>
#include <iostream>
#include <regex>
#include <fstream>
#include<vector>
#include <sstream>

void parseQuery(std::string &command, const std::shared_ptr<CMemory_Database> &db, std::ostream &ofstream);

int main(int argc, char **argv) {

    if (argc == 1) {
        std::cout << std::endl;
        std::string command;
        std::cout << "Welcome in KIV/CPP semestral work - memory database." << std::endl <<
                     "Please, enter your query." << std::endl;
        std::cout << std::endl << "> ";
        auto db = std::make_shared<CMemory_Database>();
        std::ostream stream(std::cout.rdbuf());
        while (std::getline(std::cin, command)) {
            parseQuery(command, db, stream);
        }
    } else if (argc == 3) {
        std::string input = argv[1];
        std::string output = argv[2];
        std::ifstream inStream(input, std::ios::in);
        std::ofstream stream(output, std::ios::out);
        if (!stream || !inStream) {
            std::cout << "bad params!" << std::endl;
            exit(2);
        }
        std::string temp;
        auto db = std::make_shared<CMemory_Database>();
        while (std::getline(inStream, temp, '\n')) {
            auto neco = temp.substr(temp.size()-1, 1);
            if(temp.substr(temp.size()-1, 1) == "\r")
                temp = temp.replace(temp.size()-1, 1, "");
            parseQuery(temp, db, stream);
        }
    }
    else {
        std::cerr << "usage: " <<  std::endl << "./kiv-cpp-sp-02 "<<  std::endl << " or " <<  std::endl <<
        "./kiv-cpp-sp-02 <input file> <output file> "  << std::endl;
        exit(1);
    }
}
////////////////////////
/// helper methods START
std::tuple<std::variant<int, double, std::string, Pair>, std::vector<int>, std::vector<double>,
        std::vector<std::string>, std::vector<Pair>> splitToStructures(
        const std::vector<std::variant<int, double, std::string, Pair>>& parsedParams
        ) {

    std::variant<int, double, std::string, Pair> key;

    std::vector<int> ints;

    std::vector<double> dou;

    std::vector<std::string> strs;

    std::vector<Pair> pairs;

    key = parsedParams[0];

    for (int i = 1;i < parsedParams.size(); i++) {
        std::visit([&ints, &pairs, &dou, &strs](auto &&arg) {
            if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, int>)
                ints.push_back(arg);
            else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, Pair>)
                pairs.push_back(arg);
            else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, double>)
                dou.push_back(arg);
            else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::string>)
                strs.push_back(arg);
            else
                std::cout << "bad params" << std::endl;
        }, parsedParams[i]);
    }
    return std::make_tuple(key, ints, dou, strs, pairs);
}

Pair parsePair(const std::string& item) {
    std::regex digit("[0-9\\.]+");
    if (std::regex_match(item.substr(0, item.find(':')), digit) &&
            std::regex_match(item.substr(item.find(':') + 1, item.size() - 1), digit))
        return {std::stod(item.substr(0, item.find(':'))), std::stod(item.substr(item.find(':') + 1, item.size() - 1))};
    else if (std::regex_match(item.substr(0, item.find(':')), digit))
            return {std::stod(item.substr(0, item.find(':'))), item.substr(item.find(':') + 1, item.size() - 1)};
    else if (std::regex_match(item.substr(item.find(':') + 1, item.size() - 1), digit))
        return {item.substr(0, item.find(':')), std::stod(item.substr(item.find(':') + 1, item.size() - 1))};
    else return {item.substr(0, item.find(':')), item.substr(item.find(':') + 1, item.size() - 1)};


}

std::vector<std::variant<int, double, std::string, Pair>> parseParams(std::vector<std::string> params) {
    std::vector<std::variant<int, double, std::string, Pair>> result;
    std::regex digit("[0-9\\.]+");
    std::regex digitInt("\\d+");
    for (auto &item : params) {
        if (item.find(' ') < item.size())
            item.erase(item.find(' '), 1);

        if (item.find(':') < item.size()) {
            result.emplace_back(parsePair(item));
        }
        else if (std::regex_match(item, digitInt)) {
           result.emplace_back(std::stoi(item));
        }
        else if (std::regex_match(item, digit)) {
            result.emplace_back(std::stod(item));
        }
        else result.emplace_back(item);
    }
    return result; // insert(1, 2.0, neco, 1:neco, neco:2.0)
}


void PrintMin(std::tuple<std::string, int, double, Pair> &tup, std::ostream &ofstream) {
    ofstream << "OK" << std::endl;
    ofstream << std::get<0>(tup)<< " " << (std::get<1>(tup) == INT32_MAX ? " " : std::to_string(std::get<1>(tup)))<< " "
             << (std::get<2>(tup) == INT32_MAX ? " " : std::to_string(std::get<2>(tup)))
             << " "  << std::get<3>(tup) << " "  << std::endl;
}


void PrintMax(std::tuple<std::string, int, double, Pair> &tup, std::ostream &ofstream) {
    ofstream << "OK" << std::endl;
    ofstream << std::get<0>(tup)<< " " << (std::get<1>(tup) == -INT32_MAX ? " " : std::to_string(std::get<1>(tup)))<< " "
             << (std::get<2>(tup) == -INT32_MAX ? " " : std::to_string(std::get<2>(tup)))
             << " "  << std::get<3>(tup) << " "  << std::endl;
}

/// helper methods END
//////////////////////
void parseQuery(std::string &command, const std::shared_ptr<CMemory_Database>& db, std::ostream &ofstream) {


    using var_t = std::variant<int, double, std::string, Pair>;
    std::vector<var_t> mixed;
    std::vector<std::string> params;
    /// regular expressions
    std::regex insert(R"((INSERT|insert)\(([a-zA-Z0-9\.\:]+)(, *[a-zA-Z0-9\.\:]+){1,}\))");
    std::regex del(R"((DELETE|delete)\([a-zA-Z0-9\.\:]+\))");
    std::regex eq(R"((KEY_EQUALS|key_equals)\([a-zA-Z0-9\.\:]+\))");
    std::regex gr(R"((KEY_GREATER|key_greater)\([a-zA-Z0-9\.\:]+\))");
    std::regex lr(R"((KEY_LESSER|key_lesser)\([a-zA-Z0-9\.\:]+\))");
    std::regex va(R"((FIND_VALUE|find_value)\([a-zA-Z0-9\.\:]+\))");
    std::regex av(R"((AVERAGE|average)\(\))");
    std::regex ak(R"((AVERAGE|average)\([a-zA-Z0-9\.\:]+\))");
    std::regex xk(R"((MAX|max)\([a-zA-Z0-9\.\:]+\))");
    std::regex nk(R"((MIN|min)\([a-zA-Z0-9\.\:]+\))");
    std::regex ma(R"((MAX|max)\(\))");
    std::regex mi(R"((MIN|min)\(\))");

    if (command == "EXIT" || command == "exit") {
        ofstream << "Bye." << std::endl;
        exit(0);
    }
    /// INSERT
    else if (std::regex_match(command, insert)) {
        command = command.substr(7, command.size() - 7 - 1 ); // 7 = len of "insert"
        std::stringstream s_stream(command);
        while(s_stream.good()) {
            std::string substr;
            std::getline(s_stream, substr, ',');
            params.push_back(substr);
        }
       auto structures = splitToStructures(parseParams(params));
        if (db->Insert(std::get<0>(structures), std::get<1>(structures), std::get<2>(structures),
                   std::get<3>(structures), std::get<4>(structures))) {
            ofstream << "OK" << std::endl;
            ofstream << "1 Row(s)." << std::endl;
        }
        else {
            ofstream << "ERROR" << std::endl;
            ofstream << "This key exists." << std::endl;
        }
    }
    /// delete
    else if (std::regex_match(command, del)) {
        params.emplace_back(command.substr(7, command.size() - 7 - 1 ));
        auto structures = splitToStructures(parseParams(params));
        if (db->Delete(std::get<0>(structures))) {
            ofstream << "OK" << std::endl;
            ofstream << "1 Row(s)." << std::endl;
        } else {
            ofstream << "ERROR" << std::endl;
            ofstream << "Key not found." << std::endl;
        }
    }
    /// KEY_EQUALS
    else if (std::regex_match(command, eq)) {
        params.emplace_back(command.substr(11, command.size() - 11 - 1));
        auto structures = splitToStructures(parseParams(params));
        auto res = db->Search_Key(std::get<0>(structures), CMemory_Database::db_operation::Equals);
        if (!res.empty()) {
            ofstream << "OK" << std::endl;
            ofstream << "1 Row(s)." << std::endl;
            ofstream << res[0] << std::endl;
        } else {
            ofstream << "ERROR" << std::endl;
            ofstream << "Key not found." << std::endl;
        }
    }
    /// KEY_greater
    else if (std::regex_match(command, gr)) {
        params.emplace_back(command.substr(12, command.size() - 12 - 1));
        auto structures = splitToStructures(parseParams(params));
        auto res = db->Search_Key(std::get<0>(structures), CMemory_Database::db_operation::Greater_Than);
        if (!res.empty()) {
            ofstream << "OK" << std::endl;
            ofstream << res.size() <<" Row(s)." << std::endl;
            for (const auto &item : res)
                ofstream << item << std::endl;
        } else {
            ofstream << "ERROR" << std::endl;
            ofstream << "Key not found." << std::endl;
        }
    }

    /// KEY_LESSER
    else if (std::regex_match(command, lr)) {
        params.emplace_back(command.substr(11, command.size() - 11 - 1));
        auto structures = splitToStructures(parseParams(params));
        auto res = db->Search_Key(std::get<0>(structures), CMemory_Database::db_operation::Less_Than);
        if (!res.empty()) {
            ofstream << "OK" << std::endl;
            ofstream << res.size() << " Row(s)." << std::endl;
            for (const auto &item : res)
                ofstream << item << std::endl;
        } else {
            ofstream << "ERROR" << std::endl;
            ofstream << "Key not found." << std::endl;
        }
    }

    /// FIND_VALUE
    else if (std::regex_match(command, va)) {
        params.emplace_back(command.substr(11, command.size() - 11 - 1));
        auto structures = splitToStructures(parseParams(params));

        /////////////// find val
        /////////
        auto table = db->getTable();
        int counter = 0;

        /**
         * the lambda for the find value
         */
        auto lambd = [&table, &counter, &ofstream](auto &arg) {
            return std::visit([&table, &counter, &ofstream](auto&& arg) {
            if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, int>) {
                for (auto &item : table) {
                    for (auto &info : item.getDataInt()) {
                        if (info == arg)
                            counter++;
                    }
                }
                if (counter > 0)
                    return true;
            }
            else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, Pair>) {
                for (const auto &item : table) {
                    for (const auto &info : item.getDataPair()) {
                        if (info == arg)
                            counter++;
                    }
                }
                if (counter > 0)
                    return true;
            }
            else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, double>) {
                for (const auto &item : table) {
                    for (const auto &info: item.getDataDouble()) {
                        if (info == arg)
                            counter++;
                    }
                }
                if (counter > 0)
                    return true;
            }
            else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::string>) {
                for (const auto &item : table) {
                    for (const auto &info : item.getDataStr()) {
                        if (info == arg)
                            counter++;
                    }
                }
                if (counter > 0)
                    return true;
            }
            else {
                ofstream << "neco " << std::endl;
                return false;
            }
            return false;
        }
        , arg);};
        if(db->Find_Value(lambd(std::get<0>(structures))))  {
            ofstream << "OK" << std::endl;
            ofstream << counter << " values found." << std::endl;
        } else {
            ofstream << "ERROR" << std::endl;
            ofstream << "Value not found." << std::endl;
        }
    }

    /// Average()
    else if (std::regex_match(command, av)) {

        auto res = db->Average();
        if (res != INT32_MAX) {
            ofstream << "OK" << std::endl;
            ofstream << res << " average." << std::endl;
        } else {
            ofstream << "ERROR" << std::endl;
            ofstream << "Values not found." << std::endl;
        }
    }

    /// Average(something)
    else if (std::regex_match(command, ak)) {
        params.emplace_back(command.substr(8, command.size() - 8 - 1));
        auto structures = splitToStructures(parseParams(params));
        try {
        auto res = db->Average(std::get<0>(structures));

        if (res != INT32_MAX) {
            ofstream << "OK" << std::endl;
            ofstream << res << " average." << std::endl;
        } else {
            ofstream << "ERROR" << std::endl;
            ofstream << "Values not found." << std::endl;
        }
        } catch (std::string neco) {
            std::cerr << neco << std::endl;
        }
    }

    /// MAX()
    else if (std::regex_match(command, ma)) {
    try{
        auto tup = db->Max();
        PrintMax(tup, ofstream);
        } catch (...) {
            ofstream << "ERROR" << std::endl;
            ofstream << "Values not found." << std::endl;
        }
    }

        /// MAX(something)
    else if (std::regex_match(command, xk)) {
        params.emplace_back(command.substr(4, command.size() - 4 - 1));
        auto structures = splitToStructures(parseParams(params));
        try{
            auto tup = db->Max(std::get<0>(structures));
            PrintMax(tup, ofstream);
        } catch (...) {
            ofstream << "ERROR" << std::endl;
            ofstream << "Values not found." << std::endl;
        }
    }


    /// MIN()
    else if (std::regex_match(command, mi)) {
        try{
            auto tup = db->Min();
            PrintMin(tup, ofstream);
        } catch (...) {
            ofstream << "ERROR" << std::endl;
            ofstream << "Values not found." << std::endl;
        }
    }

    /// MIN(something)
    else if (std::regex_match(command, nk)) {
        params.emplace_back(command.substr(4, command.size() - 4 - 1));
        auto structures = splitToStructures(parseParams(params));
        try{
            auto tup = db->Min(std::get<0>(structures));
            PrintMin(tup, ofstream);
        } catch (...) {
            ofstream << "ERROR" << std::endl;
            ofstream << "Values not found." << std::endl;
        }
    }
    else {
        ofstream << "bad command" << std::endl;
    }


    ofstream << std::endl << "> ";
}
