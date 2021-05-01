﻿#ifndef PROJECT_PHOTOLIST_H
#define PROJECT_PHOTOLIST_H

#include <functional>
#include <Photo.h>
#include <Utility.h>
#include <Storage.h>
#include <InterfaceScreen.h>
#include <CMenu.h>
#include <AccountList/AccountList.h>

using std::function;
using std::endl;
using std::cout;

class PhotoList : public InterfaceScreen {
public:
    using SortOrderFunction = function<bool(const Photo *, const Photo *)>;
    using FilterFunction = function<bool(const Photo *)>;

    PhotoList(const PhotoList &) = delete;

    PhotoList &operator=(const PhotoList &) = delete;

    static PhotoList *createScreen();

    int start() override;

    void renderMain() const override;

    static CMenu *createMenu();

    void addNewPhoto();

    void editPhoto();

    void deletePhoto();

    void printAllPhotos() const;

private:
    Storage *m_storage{};
    bool m_is_running{};

    void _init();

    Account::AccountsList _getMarkedAccounts();

    PhotoList();
};


#endif //PROJECT_PHOTOLIST_H