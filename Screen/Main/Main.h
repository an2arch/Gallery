#ifndef GALLERY_MAIN_H
#define GALLERY_MAIN_H


#include <InterfaceScreen.h>
#include <CMenu.h>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;


/*
 * Главный экран программы
 * Он обеспечивает следующую логику:
 * TODO: сделать описание класса
 */
class Main : public InterfaceScreen {
public:
    // удаляем конструктор копирования
    Main(const Main &) = delete;

    // удаляем оператор присваивания
    Main &operator=(const Main &) = delete;

    // метод возвращает указатель на объект экрана
    static Main *createScreen();

    // точка входа в экран
    int start() override;

    // метод выполняет главную отрисовку экрана
    void renderMain() const override;

    // метод генерации меню
    // на основе уровня доступа текущего пользователя
    CMenu *createMainMenu();


    // метод открытия списка фотографий
    void openPhotoListScreen();

    // метод открытия списка пользователей
    void openUsersListScreen();

    // метод открытия списка задач
    void openAlbumsListScreen();

    // метод разлогинивания
    void logout();

protected:
    Storage *m_storage{}; // указатель на объект хранилища

    // метод выполняет начальную инициализацию экрана
    void _init();

    // закрываем конструктор по умолчанию
    Main();
};


#endif //GALLERY_MAIN_H
