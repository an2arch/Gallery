#include "AccountList.h"

void AccountList::_init() {}

AccountList::AccountList() {
    _init();
}

AccountList *AccountList::createScreen() {
    static auto *accountList = new AccountList{};
    return accountList;
}

int AccountList::start() {
    m_storage = Storage::getStorage();
    renderMain();
    CMenu &menu = *createMenu();
    m_is_running = true;
    while (m_is_running) {
        cout << menu;
        cin >> menu;
        menu();
    }
    delete &menu;
    return 0;
}

void AccountList::renderMain() const {
    tool::clearScreen();
    cout << "Список всех пользователей\n";
    cout << "=========================\n" << endl;
    printAllAccounts();
}

CMenu *AccountList::createMenu() {
    AccountList *accountList = AccountList::createScreen();

    auto *menu = new CMenu{"Что бы вы хотели сделать?", ItemList{
            ItemMenu{"Отобразить все акаунты", [accountList]() -> int {
                accountList->printAllAccounts();
                return 1;
            }},
            ItemMenu{"Добавить новый аккаунт", [accountList]() -> int {
                accountList->addNewAccount();
                return 2;
            }},
            ItemMenu{"Редактировать аккаунт", [accountList]() -> int {
                accountList->editAccount();
                return 3;
            }},
            ItemMenu{"Удалить аккаунт", [accountList]() -> int {
                accountList->deleteAccount();
                return 4;
            }},
            ItemMenu{"Сортировка аккаунтов по имени", [accountList]() -> int {
                accountList->sortAccountsByName();
                return 5;
            }},
            ItemMenu{"Показать администраторов", [accountList]() -> int {
                accountList->filterAccountsByAdmins();
                return 6;
            }},
            ItemMenu{"Показать пользователей", [accountList]() -> int {
                accountList->filterAccountsByUsers();
                return 7;
            }},
            ItemMenu{"Вернуться назад", [accountList]() -> int {
                accountList->m_is_running = false;
                return 8;
            }},
    }};
    return menu;
}

void AccountList::addNewAccount() {
    cout << "\nДобавление нового аккаунта\n"
         << "==========================\n" << endl;

    auto state = m_storage->getState();

    Account newAccount{};

    newAccount.id = Account::current_user_id++;

    newAccount.name = tool::getEnteredString("Введите новое имя -> ");

    newAccount.login = tool::getEnteredString("Введите новый логин -> ", [state](const string &login) -> bool {
        return std::all_of(state.accounts.cbegin(), state.accounts.cend(), [login](const auto &acc) -> bool {
            return login != acc->name;
        });
    });

    newAccount.password = tool::getEnteredString("Введите новый пароль -> ");

    newAccount.level_access = (tool::getEnteredString("Введите уровень доступа -> ", [](const string &level) -> bool {
        if (level == "Admin" || level == "User") {
            return true;
        }
        return false;
    }) == "Admin" ? Account::LevelAccess::Admin : Account::LevelAccess::User);

    m_storage->dispatch(Action{
            ActionTypes::ADD_NEW_USER,
            &newAccount
    });

    cout << "\nПользователь успешно добавлен\n";
    cout << "=============================\n" << endl;
}

void AccountList::editAccount() {
    cout << "\nРедактирование аккаунта\n"
         << "=======================\n" << endl;
    printAllAccounts();

    auto state = m_storage->getState();
    Account account{};

    account.id = tool::getEnteredNum(
            "Введите id нужного пользователя -> ",
            [state](int entered) -> bool {
                return std::any_of(state.accounts.begin(), state.accounts.end(),
                                   [entered](const auto &acc) -> bool {
                                       return static_cast<unsigned int>(entered) == acc->id;
                                   });
            });
    auto notEmpty = [](const string &entered) -> bool {
        return !entered.empty();
    };
    account.name = tool::getEnteredString("Введите новое имя -> ", notEmpty);
    account.login = tool::getEnteredString("Введите новый логин аккаунта -> ", notEmpty);
    account.password = tool::getEnteredString("Введите новый пароль -> ", notEmpty);
    account.level_access = (tool::getEnteredString("Введите новый уровень доступа ->", [](const string &text) -> bool {
        return (text == "Admin") || (text == "User");
    }) == "Admin" ? Account::LevelAccess::Admin : Account::LevelAccess::User);

    m_storage->dispatch(Action{
            ActionTypes::EDIT_USER,
            &account
    });

    cout << "\nАккаунт успешно отредактирован\n"
         << "==============================\n" << endl;
}

void AccountList::deleteAccount() {
    cout << "\nУдаление аккаунта\n"
         << "=================\n" << endl;

    printAllAccounts();

    auto state = m_storage->getState();

    size_t accountIdToDelete = tool::getEnteredNum(
            "Введите id аккаунта -> ",
            [state](int id) -> bool {
                return std::any_of(state.accounts.begin(), state.accounts.end(),
                                   [id, state](const auto &acc) -> bool {
                                       return static_cast<unsigned int>(id) == acc->id &&
                                              acc.get() != state.current_user;
                                   });
            });

    size_t indexAccount{};

    for (const auto &account : state.accounts) {
        if (account->id == accountIdToDelete) {
            break;
        }
        ++indexAccount;
    }

    m_storage->dispatch(Action{
            ActionTypes::DELETE_USER,
            &indexAccount
    });

    cout << "\nАккаунт успешно удалён\n"
         << "======================\n" << endl;
}

void AccountList::sortAccountsByName() const {
    cout << "\nСортировка аккаунтов по имени\n"
         << "===============================\n" << endl;

    printAccountList([](const auto &first, const auto &second) -> bool {
        return first->name < second->name;
    }, nullptr);

    cout << "===============================\n" << endl;
}

void AccountList::filterAccountsByAdmins() const {
    cout << "\nСписок администраторов\n"
         << "=======================\n" << endl;

    printAccountList(nullptr,
                     [](const auto &account) -> bool {
                         return account->level_access == Account::LevelAccess::Admin;
                     });

    cout << "=======================\n" << endl;
}

void AccountList::filterAccountsByUsers() const {
    cout << "\nСписок пользователей\n"
         << "=====================\n" << endl;

    printAccountList(nullptr,
                     [](const auto &account) -> bool {
                         return account->level_access == Account::LevelAccess::User;
                     });

    cout << "=======================\n" << endl;
}

void AccountList::printAccountList(const AccountList::SortOrderFunction &sortOrderFunc,
                                   const AccountList::FilterFunction &filterFunc) const {
    auto accountList = m_storage->getState().accounts;

    Account::AccountsList newAccountList{accountList};

    if (sortOrderFunc) {
        newAccountList = tool::sort(newAccountList, sortOrderFunc);
    }

    if (filterFunc) {
        newAccountList = tool::filter(newAccountList, filterFunc);
    }

    tool::printTable(newAccountList);
}

void AccountList::printAllAccounts() const {
    cout << "\nСписок аккаунтов\n";
    cout << "================\n" << endl;
    printAccountList();
}
