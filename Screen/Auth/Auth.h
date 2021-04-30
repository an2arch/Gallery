#ifndef PROJECT_AUTH_H
#define PROJECT_AUTH_H

#include <iostream>
#include <InterfaceScreen.h>
#include <Account.h>
#include <Utility.h>

using std::cout;
using std::cin;
using std::endl;

using namespace tool;

class Auth : public InterfaceScreen {
public:
    // удаляем конструктор копирования
    Auth(const Auth &) = delete;

    // удаляем оператор присваивания
    Auth &operator=(const Auth &) = delete;

    // метод возвращает указатель на объект экрана
    static Auth *createScreen();

    // точка входа в экран
    int start() override;

    // метод выполняет главную отрисовку экрана
    void renderMain() const override;

    // метод авторизации
    // возвращает указатель на пользователя
    // который вошёл в систему
    Account *auth();

protected:
    Storage *m_storage{}; // указатель на объект хранилища

    // метод выполняет начальную инициализацию экрана
    void _init();

    // закрываем конструктор по умолчанию
    Auth();
};


#endif //PROJECT_AUTH_H
