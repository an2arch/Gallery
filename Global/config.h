#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

/*
 * Сюда мы помещаем глобальные ресурсы
 * доступ к которым будет осуществляться
 * из любой части нашей программы
 */

// набор идентификаторов экранов
enum IdScreens : int {
    // TODO: Сюда помещаем описание всех наших экранов
    //  которые есть в вашем приложении

    AUTH,
    MAIN,
    PHOTOLIST,
    ACCOUNTLIST,
    ALBUMLIST
};

#endif //PROJECT_CONFIG_H
