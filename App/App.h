#ifndef COSMODROME_APP_H
#define COSMODROME_APP_H

#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <Storage.h>
#include <State.h>
#include <CMenu.h>
#include <ItemMenu.h>
#include <InterfaceScreen.h>
#include <Auth/Auth.h>
#include <Main/Main.h>
#include <AccountList/AccountList.h>
#include <PhotoList/PhotoList.h>
#include <AlbumList/AlbumList.h>
#include <config.h>

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>

#endif

using std::stack;
using std::map;
using std::string;
using std::cout;

class App {
public:
    App(const App &) = delete;

    App &operator=(const App &) = delete;

    static App &createApp();

    int start();

    ~App();

private:
    App();

    Storage &m_storage;

    InterfaceScreen *m_current_screen{};

    StackScreens m_stack_screens{};

    bool m_is_run{};

    void _init();

    bool _pushStackCurrentScreen();

    bool _pullStackCurrentScreen();

    // метод запуска транзакции экрана
    // он отвечает за обработку действий после закрытия какого - либо экрана
    // именно этот метод обрабатывает
    // дальнейшие действия, после выхода из текущего экрана
    void _startTransactionScreen();
};


#endif //COSMODROME_APP_H
