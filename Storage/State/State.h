#ifndef PROJECT_STATE_H
#define PROJECT_STATE_H

#include <string>
#include <Account.h>
#include <Photo.h>
#include <Album.h>


using std::string;

struct State {
    // TODO: Сюда добавляем поля для данных нашего приложения
    string app_name{}; // название приложения
    Account *current_user{}; // указатель на текущего пользователя
    Account::AccountsList accounts{}; // список указателей на пользователей
    Photo::PhotosList photos{}; // список указателей на фотографии
    Album::AlbumsList albums{}; // список указателей на альбомы
    void *intent_next_screen{}; // указатель, который может хранить следующий запускаемый экран
    void *intent_data{}; // указатель, который может хранить данные для другого экрана
    bool is_push_stack{}; // нужно ли класть текущий экран в стэк
    void *screens_map{}; // указатель на словарь экранов программы

    template<class Archive>
    void serialize(Archive &archive) {
        archive(accounts, photos, albums);
    }
};


#endif //PROJECT_STATE_H
