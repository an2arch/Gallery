#ifndef PROJECT_STORAGE_H
#define PROJECT_STORAGE_H

#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <State.h>
#include <Action.h>
#include <ActionTypes.h>
#include <Account/Account.h>
#include <Utility.h>
#include <memory>

#include <cereal/archives/json.hpp>

using std::string;
using std::ofstream;
using std::ifstream;

/*
 * Класс - синглтон, который управляет состояниями и данными всего приложения
 *
 * Синглтон - класс, от которого можно создать лишь
 * один объект на всё приложение, достигается путём создание
 * статического объекта и закрытия конструкторов и опертора присваивания
 *
 * Состояние приложения - данные, которые описывают состояние эелемнтов
 * приложения (что выведено на экране, что выбрал пользователь и т д),
 * а также к ним относятся сами данные, с которыми работает приложение
 */
class Storage {
public:
    // удаляем конструктор копирования
    Storage(const Storage &) = delete;

    // удаляем оператор присваивания
    Storage &operator=(const Storage &) = delete;

    static Storage &createStorage(const string &path);
    // перегруженная версия метода возврата объекта
    // принимает начальное состояние и путь к корневой папке с данными
    static Storage &createStorage(State state, const string &path);

    // метод возвращает указатель на текущий объект
    static Storage *getStorage();

    // деструктор стора
    ~Storage();

    // метод, который будет обновлять состояние хранилища
    // на вход принимает объект структуры ActionTypes
    // возвращает новое состояние приложения
    State dispatch(Action action);

    // метод получения состояния нашего приложения
    State getState();


private:
    // закрываем конструктор
    explicit Storage(const string &path);

    // закрываем главный конструктор
    Storage(State state, string path);

    // объект хранилища
    State m_state{};

    // храним указатель на текущий объект
    static Storage *s_storage;

    string m_path_to_save{};

    // метод начальной инициализации Store
    void _init();

    // метод обработки событий
    State _reducer(Action action);

    // метод загрузки state
    bool _loadState();

    // метод сохранения state
    bool _saveState();
};

#endif //PROJECT_STORAGE_H
