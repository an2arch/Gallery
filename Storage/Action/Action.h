#ifndef GALLERY_ACTION_H
#define GALLERY_ACTION_H

#include <ActionTypes.h>

/*
 * Структура, которая описывает какие данные и на что
 * нужно заменить
 * Является тем самым событием, которое обрабатывает reducer
 * первым параметром идёт тип события
 * вторым параметром неопределённый указатель
 * на данные
 */
struct Action {
    ActionTypes type{};
    void *data{};
};

#endif //GALLERY_ACTION_H
