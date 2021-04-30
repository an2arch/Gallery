#include "Main.h"


// выполняем начальную инициализацию экрана
void Main::_init() {
    // TODO: инициализируем начальное состояние экрана
}

Main::Main() {
    // выполняем начальную настройку экрана
    _init();
}

// возвращаем указатель на созданный объект
// текущего класса экрана
Main *Main::createScreen() {
    static Main *main = new Main();

    return main;
}

// метод, главная точка входа в экран
int Main::start() {
    // TODO: пишем логику экрана здесь

    // получаем указатель на объект хранилища
    m_storage = Storage::getStorage();

    // отрисовываем шапку экрана
    renderMain();

    // создаём новое меню приложения
    CMenu &menu = *createMainMenu();

    // выводим меню
    cout << menu;

    // ожидаем ввод от пользователя
    cin >> menu;

    // запускаем заданную функцию
    menu();

    // удаляем меню
    delete &menu;

    return 0;
}

void Main::renderMain() const {
    system("cls");

    cout << "Добро пожаловать в главное меню, "
         << m_storage->getState().current_user->name << "!\n"
         << "============================================\n\n"
         << endl;
}

CMenu *Main::createMainMenu() {
    // получаем указатель на текущий экран
    Main *main = Main::createScreen();

    // создаём меню со стандартными пунктами
    auto *menu = new CMenu("Главное меню", ItemList{
            ItemMenu{"Открыть список фотографий", [main]() -> int {
                main->openPhotoListScreen();
                return 1;
            }},
            ItemMenu{"Открыть списов альбомов", [main]() -> int {
                main->openAlbumsListScreen();
                return 1;
            }},
            ItemMenu("Выйти из учётных данных", [main]() -> int {
                main->logout();
                return 1;
            })
    });

    // если текущий пользователь является админом
    // добавляем туда дополнительные пункты
    if (m_storage->getState().current_user->level_access == Account::LevelAccess::Admin) {
        menu->addItemByIndex(ItemMenu("Открыть список пользователей", [main]() -> int {
            main->openUsersListScreen();
            return 1;
        }), 2);
    }

    return menu;
}

void Main::openPhotoListScreen() {
    m_storage->dispatch(Action{
            ActionTypes::SET_INTENT_NEXT_SCREEN,
            static_cast<MapScreens *>(m_storage->getState().screens_map)->at(IdScreens::PHOTOLIST)
    });

    m_storage->dispatch(Action{
            ActionTypes::PUSH_STACK_SCREEN
    });
}

void Main::openUsersListScreen() {
    // задаём нужный экран для открытия
    m_storage->dispatch(Action{
            ActionTypes::SET_INTENT_NEXT_SCREEN,
            static_cast<MapScreens *>(m_storage->getState().screens_map)->at(IdScreens::ACCOUNTLIST)
    });

    // задаём триггер о том, что текущий экран следует поместить в стэк
    m_storage->dispatch(Action{
            ActionTypes::PUSH_STACK_SCREEN
    });
}

void Main::openAlbumsListScreen() {
    // задаём нужный экран для открытия
    m_storage->dispatch(Action{
            ActionTypes::SET_INTENT_NEXT_SCREEN,
            static_cast<MapScreens *>(m_storage->getState().screens_map)->at(IdScreens::ALBUMLIST)
    });

    // задаём триггер о том, что текущий экран следует поместить в стэк
    m_storage->dispatch(Action{
            ActionTypes::PUSH_STACK_SCREEN
    });
}

void Main::logout() {
    // задаём нужный экран для открытия
    m_storage->dispatch(Action{
            ActionTypes::SET_INTENT_NEXT_SCREEN,
            static_cast<MapScreens *>(m_storage->getState().screens_map)->at(IdScreens::AUTH)
    });

    // делаем разлогин
    m_storage->dispatch(Action{
            ActionTypes::CLEAR_CURRENT_USER
    });
}
