#ifndef GALLERY_UTILITY_H
#define GALLERY_UTILITY_H

#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <sstream>
#include <limits>
#include <concepts>

#include <vector>

using std::vector;
using std::string;
using std::istringstream;
using std::cout;
using std::cin;

namespace tool {
    // TODO: хорошо бы функции валидаторы переписать таким образом
    //  чтобы они возвращали не только bool, но ещё и строку
    //  с ошибкой, чтобы пользователь знал точнее, что не так

    using ValidateString = std::function<bool(string)>;

    using ValidateNum = std::function<bool(int)>;

    using ValidateChar = std::function<bool(char)>;

    string getEnteredString(const string &text, const ValidateString &validate = nullptr, std::istream &in = cin);

    int getEnteredNum(const string &text, const ValidateNum &validate = nullptr, std::istream &in = cin);

    vector<int> getEnteredInts(const string &text, const ValidateNum &validate = nullptr, std::istream &in = cin);

    void clearScreen();

    template<typename T, typename Order>
    requires std::relation<Order, T, T>
    vector<T> sort(const vector<T> &acc, Order order) {
        vector<T> sorted{acc};
        std::sort(sorted.begin(), sorted.end(), order);
        return sorted;
    }

    template<typename T, typename Predicate>
    requires std::predicate<Predicate, T>
    vector<T> filter(const vector<T> &acc, Predicate pred) {
        vector<T> filtered{};
        for (const auto &element : acc) {
            if (pred(element)) {
                filtered.push_back(element);
            }
        }
        return filtered;
    }

    template<typename T, typename Predicate>
    requires std::predicate<Predicate, T>
    bool all_of(const vector<T> &vector, Predicate pred) {
        for (const auto &item : vector) {
            if (!pred(item)) {
                return false;
            }
        }
        return true;
    }

    template<typename T, typename Predicate>
    requires std::predicate<Predicate, T>
    bool any_of(const vector<T> &vector, Predicate pred) {
        for (const auto &item : vector) {
            if (pred(item)) {
                return true;
            }
        }
        return false;
    }
}

#endif //GALLERY_UTILITY_H
