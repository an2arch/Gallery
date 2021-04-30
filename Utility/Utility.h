#ifndef PROJECT_UTILITY_H
#define PROJECT_UTILITY_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <sstream>

using std::vector;
using std::string;
using std::istringstream;
using std::cout;
using std::cin;

using namespace std::chrono;

namespace tool {
    /*
 * Функции в этом файле принимают валидаторы
 *
 * Валидатор - это функция, которая на основании
 * переданного ей значения возвращает логичеескую переменную
 * значение которой сообщает подходит ли нам пользовательский ввод,
 * или нет
 *
 * Функции валидаторы имеют общий интерфейс оисанный здесь
 *
 * Сами функции валидаторы - объявляются там, где используются
 */

    // TODO: хорошо бы функции валидаторы переписать таким образом
    //  чтобы они возвращали не только bool, но ещё и строку
    //  с ошибкой, чтобы пользователь знал точнее, что не так

    // интерфейс для валидирования ввода строки
    // создаём указатель на функцию через класс function
    // чтобы мы могли использовать лямбда - функции
    // почти аналогично строке:
    // using ValidateString = bool (*)(string);
    using ValidateString = std::function<bool(string)>;

    // интерфейс для валидирования ввода числа
    // создаём указатель на функцию через класс function
    // чтобы мы могли использовать лямбда - функции
    // почти аналогично строке:
    // using ValidateNum = bool (*)(int);
    using ValidateNum = std::function<bool(int)>;

    // интерфейс для валидирвоания ввода символа
    // создаём указатель на функцию через класс function
    // чтобы мы могли использовать лямбда - функции
    // почти аналогично строке:
    // using ValidateChar = bool (*)(char);
    using ValidateChar = std::function<bool(char)>;

    // функция считывнаия строки с консоли
    // возвращает считанную строку
    // строку запроса, поток ввода (опционально) и
    // принимает валидатор ввода (опционально)
    string getEnteredString(const string &text, const ValidateString &validate = nullptr, std::istream &in = cin);

    // функция считывнаия числа с консоли
    // возвращает считанное число
    // строку запроса, поток ввода (опционально) и
    // принимает валидатор ввода
    int getEnteredNum(const string &text, const ValidateNum &validate = nullptr, std::istream &in = cin);

    // функция считывнаия символа с консоли
    // возвращает считанный символ
    // строку запроса, поток ввода (опционально) и
    // принимает валидатор ввода
    char getEnteredChar(const string &text, const ValidateChar &validate = nullptr, std::istream &in = cin);

    vector<int> getEnteredInts(const string &text, const ValidateNum &validate = nullptr, std::istream &in = cin);

    template<typename T>
    void swap(T &first, T &second) {
        T tmp = first;
        first = second;
        second = tmp;
    }

    template<typename T, typename Order>
    vector<T> sort(const vector<T> &acc, Order order) {
        vector<T> sorted{acc};
        std::sort(sorted.begin(), sorted.end(), order);
        return sorted;
    }

    template<typename T, typename Predicate>
    vector<T> filter(const vector<T> &acc, Predicate pred) {
        vector<T> filtered{};
        for (const auto &element : acc) {
            if (pred(element)) {
                filtered.push_back(element);
            }
        }
        return filtered;
    }
}

#endif //PROJECT_UTILITY_H
