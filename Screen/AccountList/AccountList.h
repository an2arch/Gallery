#ifndef PROJECT_ACCOUNTLIST_H
#define PROJECT_ACCOUNTLIST_H

#include <functional>
#include <algorithm>
#include <iostream>
#include <Storage.h>
#include <InterfaceScreen.h>
#include <Account.h>
#include <CMenu.h>
#include <Utility.h>

using std::cout;
using std::cin;
using std::endl;
using std::function;

class AccountList : public InterfaceScreen {
public:
    using SortOrderFunction = function<bool(const shared_ptr<Account> &, const shared_ptr<Account> &)>;
    using FilterFunction = function<bool(const shared_ptr<Account> &)>;

    AccountList(const AccountList &) = delete;

    AccountList &operator=(const AccountList &) = delete;

    static AccountList *createScreen();

    int start() override;

    void renderMain() const override;

    CMenu *createMenu();

    void addNewAccount();

    void editAccount();

    void deleteAccount();

    void sortAccountsByName() const;

    void filterAccountsByAdmins() const;

    void filterAccountsByUsers() const;

    void printAccountList(const SortOrderFunction &sortOrderFunc = nullptr,
                          const FilterFunction &filterFunc = nullptr) const;

    void printAllAccounts() const;

private:
    AccountList();

    Storage *m_storage{};
    bool m_is_running{};

    void _init();
};

#endif //PROJECT_ACCOUNTLIST_H
