#ifndef GALLERY_ACTIONTYPES_H
#define GALLERY_ACTIONTYPES_H

enum class ActionTypes {
    //  Здесь описываем типы всех действий в нашем приложении
    //  а точнее, виды всех событий, которые могут произойти в нашей программе
    //  эти события будет обрабатывать метод reducer

    CHANGE_APP_NAME,
    CLEAR_CURRENT_USER,
    SET_CURRENT_USER,

    ADD_NEW_USER,
    EDIT_USER,
    DELETE_USER,

    ADD_NEW_PHOTO,
    EDIT_PHOTO,
    DELETE_PHOTO,

    ADD_NEW_ALBUM,
    EDIT_ALBUM,
    DELETE_ALBUM,

    SET_INTENT_NEXT_SCREEN,
    SET_INTENT_DATA,
    CLEAR_INTENT_NEXT_SCREEN,
    CLEAR_INTENT_DATA,
    PUSH_STACK_SCREEN,
    CLEAR_PUSH_STACK_SCREEN
};

#endif //GALLERY_ACTIONTYPES_H
