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

// метод, главная точка входа в экран
int Auth::start() {
    // получаем указатель на объект хранилища
    m_storage = Storage::getStorage();

    // выполняем отрисовку шапки
    renderMain();

    CMenu &menu = *Auth::createAuthMenu();
    m_continue = true;

    cout << menu;
    cin >> menu;
    menu();

    // теперь устанавливаем экран, который будет открыт следующим
    if (m_continue) {
        m_storage->dispatch(Action{
                ActionTypes::SET_INTENT_NEXT_SCREEN,
                static_cast<MapScreens *>(m_storage->getState().screens_map)->at(IdScreens::MAIN)
        });
    }

    return 0;
}

CMenu *Auth::createAuthMenu() {
    // auto state = m_storage->getState();
    auto authScreen = Auth::createScreen();
    auto *menu = new CMenu{"Меню авторизации", ItemList{
            ItemMenu{"Авторизизроваться", [authScreen]() -> int {
                Account *account{};

                // запускаем цикл авторизации
                // если пользователь ввёл неверные данные
                // запрашиваем их у него ещё раз
                for (account = authScreen->auth(); !account; account = authScreen->auth()) {
                    cout << "\n\nПользователя с таким логином и паролем не существует! Попробуйте ещё раз!\n\n" << endl;
                }

                // если авторизация прошла, то в user лежит указатель на успешно вошедшего пользователя
                // делаем его текущим
                // вызываем у хранилища метод диспач
                // и передаём ему объект события
                // первым параметром идёт тип события
                // вторым - указатель на пользователя
                // который мы конвертировали в неопределённый указатель
                authScreen->m_storage->dispatch(Action{
                        ActionTypes::SET_CURRENT_USER,
                        static_cast<void *>(account)
                });

                return 0;
            }},
            ItemMenu{"Зарегистрироваться", [authScreen]() -> int {
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
    // стираем всё с экрана
    tool::clearScreen();

    cout << "Добро пожаловать" << endl;
    cout << "===============================================\n\n";
    cout << "Чтобы продолжить Вам необходимо авторизироваться\n"
            "по вашим личным данным - login/password,\n"
            "если Вы не знаете, или не помните свои авторизационные\n"
            "данные свяжитесь с администратором!\n";
    cout << "-----------------------------------------------\n" << endl;
}

// здесь мы выполняем авторизациюю пользователя
// и возвращаем указатель на авторизировавшигося пользователя
Account *Auth::auth() {
    // запрашиваем у пользователя логин
    string login = getEnteredString("Введите логин -> ", validateEnter);

    // запрашиваем у пользователя пароль
    // точно также, пароль не должен быть пустым
    string password = getEnteredString("Введите пароль -> ", validateEnter);

    // ищем пользователя по полученному логину
    for (const auto &user : m_storage->getState().accounts) {
        if (user->login == login) {
            // если нашли совпадение, проверяем пароль
            if (user->password == password) {
                // всё хорошо? - отправляем указатель на пользователя
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

    account->name = tool::getEnteredString("Введите ваше имя -> ");

    account->login = tool::getEnteredString("Введите логин -> ", [state](const string &login) -> bool {
        return !login.empty() &&
               std::all_of(state.accounts.begin(), state.accounts.end(), [&login](const auto account) -> bool {
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
