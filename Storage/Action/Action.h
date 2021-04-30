#ifndef PROJECT_ACTION_H
#define PROJECT_ACTION_H

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

#endif //PROJECT_ACTION_H
