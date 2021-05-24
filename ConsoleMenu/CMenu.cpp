#include "CMenu.h"

CMenu::CMenu(string title, ItemList itemList)
        : m_title(std::move(title)), m_items(std::move(itemList)) {}

void CMenu::print(std::ostream &out) const {
    out << m_title << std::endl;
    out << "============================\n";

    size_t index{1};

    // выводим пункты по одному
    for (const auto &item : m_items) {
        out << index++ << ". " << item << '\n';
    }

    out << std::endl;
}

void CMenu::selectItem(size_t selected) {
    // делаем проверку на диапозон
    if (selected <= m_items.size() && selected > 0) {
        m_selected = selected - 1;
    } else {
        m_selected = -1;
    }
}

int CMenu::execSelected() const {
    // выполняем проверку
    if (m_selected == -1) {
        return -1;
    }

    // если всё хорошо запускаем
    return m_items.at(m_selected)();
}

int CMenu::operator()() const {
    return execSelected();
}

std::ostream &operator<<(std::ostream &out, const CMenu &menu) {
    menu.print(out);

    return out;
}

int CMenu::getSelected() const {
    return m_selected;
}

std::istream &operator>>(std::istream &in, CMenu &menu) {
    int selected = tool::getEnteredNum(
            "Введите номер нужного пункта -> ",
            getValidate(menu.m_items.size()),
            in
    );
    menu.selectItem(selected);

    return in;
}

void CMenu::addItem(const ItemMenu &itemMenu) {
    m_items.push_back(itemMenu);
}

void CMenu::addItemByIndex(const ItemMenu &itemMenu, size_t index) {
    // проверяем, что указанный индекс входит в заданный диапазон
    if (index < m_items.size()) {
        m_items.insert(m_items.begin() + static_cast<int>(index), itemMenu);
    }
}

// функция возвращает нужный валидатор для ввода
// принимает кол - во эелемнтов в меню
tool::ValidateNum getValidate(int count_items) {
    // возвращаем лямбду функцию
    // с замыканием кол - ва эелемнтов в меню
    return [count_items](int value) -> bool {
        return (value <= count_items && value > 0);
    };
}
