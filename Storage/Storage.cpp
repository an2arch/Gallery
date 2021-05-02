﻿#include "Storage.h"


// инициализируем указатель на текущий объект
// в данном случае он равен нулевому указателю
Storage *Storage::s_storage{};

// метод, который загружает данные в state
// из базы данных
// база данных представляем из себя класс - синглтон
// и имеет методы для выгрузки
// и загрузки данных
bool Storage::_loadState() {
    ifstream fin{m_path_to_save};

    if (fin) {
        cereal::PortableBinaryInputArchive archive{fin};
        archive(m_state);
    } else {
        m_state.accounts.push_back(std::make_shared<Account>(Account{
                .name = "Admin",
                .id = Account::current_user_id++,
                .login = "admin",
                .password = "admin",
                .level_access = Account::LevelAccess::Admin
        }));
    }
    // если всё успешно - возвращаем true
    return true;
}

// в этом методе происходит сохранение State
// в объекте базы
bool Storage::_saveState() {
    // TODO: Реализовать сохранение состояния приложения
    ofstream fout{m_path_to_save};

    if (!fout) {
        return false;
    }

    cereal::PortableBinaryOutputArchive archive{fout};
    archive(m_state);

    return true;
}

// метод инициализации хранилища
void Storage::_init() {
    // TODO: Здесь описываем начаьную инициализацию Storage

    // загружаем данные и проверяем на ошибку
    if (bool err = _loadState(); !err) {
        // не удалось загрузить данные
        // отображаем сообщение об этом в логе ошибок
        std::cerr
                << "Не удалось загрузить начальные данные хранилища! Storage.cpp - _init()"
                << std::endl;
    }
}

Storage::~Storage() {
    // TODO: сохраняем данные и очищаем что нужно

    // пытаемся сохраниться
    if (bool err = _saveState(); !err) {
        // не удалось сохранить данные
        // отображаем сообщение об этом в логе ошибок
        std::cerr
                << "Не удалось сохранить данные хранилища! Storage.cpp - ~Storage()"
                << std::endl;
    }
}

// конструктор, принимающий объект state
// с начальной инициализацией
// через список инициализации настраиваем объекты
Storage::Storage(State state, string path)
        : m_state{std::move(state)}, m_path_to_save{std::move(path)} {

    // запускаем метод начлаьной инициализации Storage
    _init();
}

// вызываем дилегирующий конструктор
// с новым (пустым) объектом State
Storage::Storage(const string &path) : Storage(State{}, path) {}

Storage &Storage::createStorage(const string &path) {
    static Storage storage{path};
    s_storage = &storage;
    return storage;
}

Storage &Storage::createStorage(State state, const string &path) {
    // создаём статический объект с начальным состоянием
    static Storage storage(std::move(state), path);

    // сохраняем указатель на этот объект
    s_storage = &storage;

    // возвращаем его
    return storage;
}

// метод, который принимает объект Action
// объект Action состоит из двух полей:
// типа события и данных
// затем, этот метод передаёт пришедший
// объект событий методу reducer
// который на основе типа события и данных
// будет менять состояние приложения
// а затем вернёт новое состояние
State Storage::dispatch(Action action) {
    // вызываем метод обработки событий
    // присваеваем новый объект состояния
    m_state = _reducer(action);

    // возвращаем его
    return m_state;
}

// метод обработки событий приложения
// сюда мы помещаем все возможные события
// которые могут возникнуть в нашей программе
// данный метод по пришедшему к нему события
// создаёт новый объект State
// заполняет его новыми данными
// которые пришли в событии и отправляет его
// обратно, сам корневой State - он не меняет
State Storage::_reducer(Action action) {
    // создаём копию состояния
    State state(m_state);

    // TODO: Здесь описываем логику событий нашего приложения в case-ах
    //  делаем проверку по типу события

    switch (action.type) {
        case ActionTypes::CHANGE_APP_NAME:
            state.app_name = *static_cast<string *>(action.data);
            break;
        case ActionTypes::SET_CURRENT_USER:
            state.current_user = static_cast<Account *>(action.data);
            break;
        case ActionTypes::CLEAR_CURRENT_USER:
            state.current_user = nullptr;
            break;
        case ActionTypes::ADD_NEW_USER:
            state.accounts.push_back(std::make_shared<Account>(Account(*static_cast<Account *>(action.data))));
            break;
        case ActionTypes::EDIT_USER:
            for (const auto &item : state.accounts) {
                if (item->id == static_cast<Account *>(action.data)->id) {
                    *item = *static_cast<Account *>(action.data);
                }
            }
            break;
        case ActionTypes::DELETE_USER:
            // delete state.accounts.at(*static_cast<int *>(action.data));
            state.accounts.erase(state.accounts.begin() + *static_cast<int *>(action.data));
            break;
        case ActionTypes::ADD_NEW_PHOTO:
            state.photos.push_back(std::make_shared<Photo>(Photo{*static_cast<Photo *>(action.data)}));
            break;
        case ActionTypes::EDIT_PHOTO:
            for (const auto &item : state.photos) {
                if (item->id == static_cast<Photo *>(action.data)->id) {
                    *item = *static_cast<Photo *>(action.data);
                }
            }
            break;
        case ActionTypes::DELETE_PHOTO:
            // delete state.photos.at(*static_cast<int *>(action.data));
            state.photos.erase(state.photos.begin() + *static_cast<int *>(action.data));
            break;

        case ActionTypes::ADD_NEW_ALBUM:
            state.albums.push_back(std::make_shared<Album>(Album{*static_cast<Album *>(action.data)}));
            break;
        case ActionTypes::EDIT_ALBUM:
            for (const auto &item : state.albums) {
                if (item->id == static_cast<Album *>(action.data)->id) {
                    *item = *static_cast<Album *>(action.data);
                }
            }
            break;
        case ActionTypes::DELETE_ALBUM:
            // delete state.albums.at(*static_cast<int *>(action.data));
            state.albums.erase(state.albums.begin() + *static_cast<int *>(action.data));
            break;
        case ActionTypes::SET_INTENT_NEXT_SCREEN:
            state.intent_next_screen = action.data;
            break;
        case ActionTypes::SET_INTENT_DATA:
            state.intent_data = action.data;
            break;
        case ActionTypes::CLEAR_INTENT_NEXT_SCREEN:
            // объекты экранов не удаляются
            // они синглтоны и должны существовать до конца программы
            // здесь мы просто обнуляем указатель на следующий экран
            state.intent_next_screen = nullptr;
            break;
        case ActionTypes::CLEAR_INTENT_DATA:
            // т к данные будут храниться, как не определённый
            // указатель на объект, удалить мы его не сможем
            // по этому удаление самого объекта ложиться
            // на плечи принимающему экрану
            // а здесь мы просто обнуляем указатель
            state.intent_data = nullptr;
            break;
        case ActionTypes::PUSH_STACK_SCREEN:
            state.is_push_stack = true;
            break;
        case ActionTypes::CLEAR_PUSH_STACK_SCREEN:
            state.is_push_stack = false;
            break;

        default:
            // какая - то общая логика обработки
            // если не нашли ничего нужного
            break;
    }

    return state;
}

// возвращаем объект состояния приложения
State Storage::getState() {
    return m_state;
}

// возвращаем указатель на статический объект хранилища
Storage *Storage::getStorage() {

    // проверка ошибки
    if (s_storage == nullptr) {
        std::cerr << "Вызов getStorage раньше чем createStorage! Получен нулевой указатель!" << std::endl;
    }

    return s_storage;
}

