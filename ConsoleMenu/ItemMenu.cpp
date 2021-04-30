#include <ItemMenu.h>
#include <utility>

ItemMenu::ItemMenu(string item_name, Function task)
        : m_name{std::move(item_name)}, m_task{std::move(task)} {}

ItemMenu::ItemMenu(const ItemMenu &other)
        : ItemMenu(other.m_name, other.m_task) {};

string ItemMenu::getItemName() const {
    return m_name;
}

void ItemMenu::print(std::ostream &out) const {
    out << m_name;
}

ItemMenu &ItemMenu::operator=(const ItemMenu &other) {
    if (this == &other) {
        return *this;
    }
    m_name = other.m_name;
    m_task = other.m_task;
    return *this;
}

std::ostream &operator<<(std::ostream &out, const ItemMenu &item) {
    item.print(out);
    return out;
}

int ItemMenu::operator()() const {
    return run();
}

int ItemMenu::run() const {
    if (m_task) {
        return m_task();
    }
    return -1;
}
