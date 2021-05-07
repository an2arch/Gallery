#ifndef PROJECT_CMENU_H
#define PROJECT_CMENU_H

#include <string>
#include <vector>
#include <iostream>
#include <ItemMenu.h>
#include <Utility.h>

using std::string;

// описываем тип вектора
// который будет хранить наши пункты меню
using ItemList = std::vector<ItemMenu>;

/*
 * Класс меню - объекты данного класса
 * будут представл¤ть из себ¤ меню пользовател¤
 * которое будет содержать запускаемые объекты
 * и позвол¤ть оперировать ими (запуская)
 * через единный интерфейс
 */
class CMenu {
public:
    // удаляем конструктор по умолчанию
    CMenu() = delete;

    // удаляем оператор присваивани¤
    CMenu &operator=(const CMenu &) = delete;

    // создаём конструктор, который принимает заголовок меню
    // и вектор функций
    CMenu(string title, ItemList itemList);

    // создаём метод печати пунктов на экране
    // который может принимать поток вывода
    void print(std::ostream &out = std::cout) const;

    // метод устанавливающий выбранный пункт меню
    void selectItem(size_t selected);

    // метод запуска пункта меню
    // возвращает код возврата вызванной функции
    [[nodiscard]] int execSelected() const;

    // перегрузка оператора исполнени¤
    // тоже делаем константным
    int operator()() const;

    // дружественна¤ функция вывода
    friend std::ostream &operator<<(std::ostream &out, const CMenu &menu);

    // дружественна¤ функци¤ ввода
    friend std::istream &operator>>(std::istream &in, CMenu &menu);

    // получить выбранный пункт
    [[nodiscard]] int getSelected() const;

    // метод добавляющий пункт меню в конец
    void addItem(const ItemMenu &itemMenu);

    // метод добавл¤ющий пункт меню на заданную позицию
    void addItemByIndex(const ItemMenu &itemMenu, size_t index);

private:
    string m_title{};
    ItemList m_items{};
    int m_selected{-1};
};

// функция возвращает нужный валидатор для ввода
// принимает кол - во элемнтов в меню
tool::ValidateNum getValidate(int count_items);

#endif //PROJECT_CMENU_H
