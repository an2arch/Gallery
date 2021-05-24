#ifndef GALLERY_ITEMMENU_H
#define GALLERY_ITEMMENU_H

#include <iostream>
#include <string>
#include <functional>

using std::string;

class ItemMenu {
public:
    using Function = std::function<int()>;

    ItemMenu() = default;

    ItemMenu(string item_name, Function task);

    ItemMenu(const ItemMenu &other);

    ItemMenu &operator=(const ItemMenu &other);

    [[nodiscard]] string getItemName() const;

    void print(std::ostream &out = std::cout) const;

    friend std::ostream &operator<<(std::ostream &out, const ItemMenu &item);

    [[nodiscard]] int run() const;

    int operator()() const;

private:
    string m_name{};
    Function m_task{};
};

#endif //GALLERY_ITEMMENU_H
