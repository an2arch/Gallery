#include "Auth.h"

// функция валидации ввода пользователя
// заметим, что эта функция не будет доступна из других
// участков программы
bool validateEnter(const string &str) {
    return !str.empty();
}

// выполняем начальную инициализацию экрана
void Auth::_init() {
    // инициализируем начальное состояние экрана
}

Auth::Auth() {
    // выполняем начальную настройку экрана
    _init();
}

// возвращаем указатель на созданный объект
// текущего класса экрана
Auth *Auth::createScreen() {
    static Auth *auth = new Auth();

    return auth;
}

int Auth::start() {
    m_storage = Storage::getStorage();

    renderMain();

    CMenu &menu = *Auth::createAuthMenu();
    m_continue = true;

    cout << menu;
    cin >> menu;
    menu();

    if (m_continue) {
        m_storage->dispatch(Action{
                ActionTypes::SET_INTENT_NEXT_SCREEN,
                static_cast<MapScreens *>(m_storage->getState().screens_map)->at(IdScreens::MAIN)
        });
    }

    return 0;
}

CMenu *Auth::createAuthMenu() {
    auto authScreen = Auth::createScreen();
    auto *menu = new CMenu{"Меню авторизации", ItemList{
            ItemMenu{"Авторизация", [authScreen]() -> int {
                Account *account;

                for (account = authScreen->auth(); !account; account = authScreen->auth()) {
                    cout << "\n\nПользователя с таким логином и паролем не существует! Попробуйте ещё раз!\n\n" << endl;
                }

                authScreen->m_storage->dispatch(Action{
                        ActionTypes::SET_CURRENT_USER,
                        static_cast<void *>(account)
                });

                return 0;
            }},
            ItemMenu{"Регистрация", [authScreen]() -> int {
                Account *account = authScreen->registration();

                authScreen->m_storage->dispatch(Action{
                        ActionTypes::ADD_NEW_USER,
                        static_cast<void *>(account)
                });

                authScreen->m_storage->dispatch(Action{
                        ActionTypes::SET_CURRENT_USER,
                        static_cast<void *>(account)
                });

                return 1;
            }},
            ItemMenu{"Выйти", [authScreen]() -> int {
                authScreen->exit();
                return 2;
            }}
    }};

    return menu;
}

void Auth::renderMain() const {
    tool::clearScreen();

    cout << "Добро пожаловать" << endl;
    cout << "===============================================\n\n";
    cout << "Чтобы продолжить Вам необходимо авторизоваться\n"
            "по вашим личным данным - login/password,\n"
            "если Вы не знаете, или не помните свои данные\n"
            "для авторизации свяжитесь с администратором!\n";
    cout << "-----------------------------------------------\n" << endl;
}

Account *Auth::auth() {
    string login = getEnteredString("Введите логин -> ", validateEnter);

    string password = getEnteredString("Введите пароль -> ", validateEnter);

    for (const auto &user : m_storage->getState().accounts) {
        if (user->login == login) {
            if (user->password == password) {
                return user.get();
            }
        }
    }

    return nullptr;
}

Account *Auth::registration() {
    auto state = m_storage->getState();

    shared_ptr<Account> account = std::make_shared<Account>(Account{});
    account->level_access = Account::LevelAccess::User;
    account->id = Account::current_user_id++;

    account->name = tool::getEnteredString("Введите ваше имя -> ", [](const string &name) -> bool {
        return !name.empty();
    });

    account->login = tool::getEnteredString("Введите логин -> ", [state](const string &login) -> bool {
        return !login.empty() &&
               tool::all_of(state.accounts, [&login](const auto account) -> bool {
                   return account->login != login;
               });
    });

    account->password = tool::getEnteredString("Введите пароль -> ", [state](const string &password) -> bool {
        return !password.empty();
    });

    return account.get();
}

void Auth::exit() {
    m_continue = false;
}
