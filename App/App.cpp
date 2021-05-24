#include "App.h"


void App::_init() {
    m_current_screen = static_cast<MapScreens *>(m_storage.getState().screens_map)->at(IdScreens::AUTH);

#if defined(_WIN32) || defined(_WIN64)
    SetConsoleOutputCP(CP_UTF8);
#endif

    m_is_run = true;
}

App::App()
        : m_storage(Storage::createStorage(
        State{
                .app_name = "Gallery",

                .screens_map = new map<int, InterfaceScreen *>{
                        {IdScreens::AUTH,         Auth::createScreen()},
                        {IdScreens::MAIN,         Main::createScreen()},
                        {IdScreens::PHOTO_LIST,   PhotoList::createScreen()},
                        {IdScreens::ALBUM_LIST,   AlbumList::createScreen()},
                        {IdScreens::ACCOUNT_LIST, AccountList::createScreen()}
                }
        }, PATH_TO_STATE)) {

    _init();
}

App &App::createApp() {
    static App app{};

    return app;
}

int App::start() {
    int code_return = 0;

    while (m_is_run) {
        code_return = m_current_screen->start();

        if (code_return != 0) {
            std::cerr << "Screen exit with error! App.cpp - start()" << std::endl;

            return code_return;
        }

        _startTransactionScreen();
    }

    return code_return;
}

bool App::_pushStackCurrentScreen() {
    if (m_current_screen) {
        m_stack_screens.push(m_current_screen);
        return true;
    }

    return false;
}

bool App::_pullStackCurrentScreen() {
    if (m_stack_screens.empty()) {
        return false;
    }

    m_current_screen = m_stack_screens.top();

    m_stack_screens.pop();

    return true;
}

App::~App() {
    MapScreens &mapScreens = *static_cast<MapScreens *>(m_storage.getState().screens_map);

    delete dynamic_cast<Auth *>(mapScreens.at(IdScreens::AUTH));
    delete dynamic_cast<Main *>(mapScreens.at(IdScreens::MAIN));
    delete dynamic_cast<AlbumList *>(mapScreens.at(IdScreens::ALBUM_LIST));
    delete dynamic_cast<PhotoList *>(mapScreens.at(IdScreens::PHOTO_LIST));
    delete dynamic_cast<AccountList *>(mapScreens.at(IdScreens::ACCOUNT_LIST));

    delete &mapScreens;
}

void App::_startTransactionScreen() {
    if (m_storage.getState().intent_next_screen) {
        if (m_storage.getState().is_push_stack) {
            _pushStackCurrentScreen();

            m_storage.dispatch(Action{
                    ActionTypes::CLEAR_PUSH_STACK_SCREEN
            });
        }

        m_current_screen = static_cast<InterfaceScreen *>(m_storage.getState().intent_next_screen);

        m_storage.dispatch(Action{
                ActionTypes::CLEAR_INTENT_NEXT_SCREEN
        });
    } else {
        if (!_pullStackCurrentScreen()) {
            m_is_run = false;
        }
    }
}
