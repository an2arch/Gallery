#ifndef GALLERY_CONFIG_H
#define GALLERY_CONFIG_H

#include <string>

using std::string;

/*
 * Сюда мы помещаем глобальные ресурсы
 * доступ к которым будет осуществляться
 * из любой части нашей программы
 */

const string PATH_TO_STATE{"./saved_state"};

// набор идентификаторов экранов
enum IdScreens : int {
    AUTH,
    MAIN,
    PHOTO_LIST,
    ACCOUNT_LIST,
    ALBUM_LIST
};

#endif //GALLERY_CONFIG_H
