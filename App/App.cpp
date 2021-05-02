#include "App.h"


void App::_init() {
    // устаналиваем начальный экран
    // с которого нужно запуститься
    // для этого мы в поле указателя на
    // текущий экран кладём указатель на
    // экран, который будет стартовать первым
    // обращаемся к объекту: state, через его метод getState
    // получаем объект State, у этого объекта
    // обращаемся к полю, которое хранит указатель
    // на словарь экранов, который используются в приложении
    // т к этот указатель является типом void мы его приобразовываем
    // к нужному нам типу, в данном случае к указателю на MapScreens
    // дальше обращаемся к словарю и получаем указател на экран
    // через его Id
    m_current_screen = static_cast<MapScreens *>(m_storage.getState().screens_map)->at(IdScreens::AUTH);

    // для винды вытворяем вокханалию
    // чтобы заработал русский язык
#if defined(_WIN32) || defined(_WIN64)
    SetConsoleOutputCP(CP_UTF8);
#endif

    // выставляем тригер на запущено
    // что позволит запустить наш
    // главный цикл обработки событий
    m_is_run = true;
}

// в этом конструкторе мы инициализируем ссылку
// на объект store в списке инициализации
// для этого мы вызываем статический метод createStore
// у стора, который возвращает новый объект стора
// этому методу мы передаём созданный здесь же объект State
// который хранит начальное состояние нашего приложения
// туда мы передаём данные для заполнения полей
// в данном случае поля будут: имя программы и словарь экранов
// кроме объекта State, мы передаём корневую директорию
// для сохранения файлов баз данных
// объявление этой корневой директории лежит в глобальных
// ресурсах проекта
App::App()
        : m_storage(Storage::createStorage(
        State{
                // TODO: настраиваем начальное состояние нашего приложения

                // устанавливаем название программы
                .app_name = "Gallery",

                .current_user = nullptr,
                .accounts = {},
                .photos = {},
                .intent_next_screen = nullptr,
                .intent_data = nullptr,
                .is_push_stack = false,

                // устанавливаем экраны программы
                // создаём в памяти словарь экранов
                // ключом будет являться Id экрана
                // а значением указатель на экран
                // каждый экран является классом - синглтоном
                // по этому вызываем их статические методы
                // которые возвращают нам указатели на объекты
                .screens_map = new map<int, InterfaceScreen *>{
                        {IdScreens::AUTH,        Auth::createScreen()},
                        {IdScreens::MAIN,        Main::createScreen()},
                        {IdScreens::PHOTOLIST,   PhotoList::createScreen()},
                        {IdScreens::ALBUMLIST,   AlbumList::createScreen()},
                        {IdScreens::ACCOUNTLIST, AccountList::createScreen()}
                }
        }, PATH_TO_STATE)) {

    // настраиваем объект приложения
    // вызываем метод инициализации
    _init();
}

App &App::createApp() {
    // создаём статический объект приложения
    static App app{};

    // возвращаем ссылку на этот объект
    return app;
}

int App::start() {
    // код возврата
    int code_return = 0;

    // главный цикл действий нашей программы
    while (m_is_run) {
        // запускаем главный экран нашего приложения
        code_return = m_current_screen->start();

        // проверяем код с которым закончил работу экран
        if (code_return != 0) {
            // если код отличен от нуля
            // значит экран отработал с ошибкой
            // завершаем работу программы, возвращая код ошибки
            // и пишем об этом в лог ошибок
            std::cerr
                    << "Экран завершился с ошибкой! App.cpp - start()"
                    << std::endl;

            return code_return;
        }

        // если всё хорошо, то запускаем обработку действий
        // после закрытия экрана
        _startTransactionScreen();

        // а теперь начинаем следующую итерацию цикла
    }

    return code_return;
}

bool App::_pushStackCurrentScreen() {
    // если имеется текущий скрин
    // то добавляем указатель на него
    // в стэк
    if (m_current_screen) {
        m_stack_screens.push(m_current_screen);
        return true;
    }

    return false;
}

bool App::_pullStackCurrentScreen() {
    // если стэк пустой
    // то возвращаем false, иначе
    // восстанавливаем последний скрин
    if (m_stack_screens.empty()) {
        return false;
    }

    // возвращаем указатель на последний экран
    m_current_screen = m_stack_screens.top();

    // удаляем его из стэка
    m_stack_screens.pop();

    return true;
}

App::~App() {
    // получаем словарь экранов
    MapScreens &mapScreens = *static_cast<MapScreens *>(m_storage.getState().screens_map);

    // бежим по экранам и удаляем их объекты из store
    delete dynamic_cast<Auth *>(mapScreens.at(IdScreens::AUTH));
    delete dynamic_cast<Main *>(mapScreens.at(IdScreens::MAIN));
    delete dynamic_cast<AlbumList *>(mapScreens.at(IdScreens::ALBUMLIST));
    delete dynamic_cast<PhotoList *>(mapScreens.at(IdScreens::PHOTOLIST));
    delete dynamic_cast<AccountList *>(mapScreens.at(IdScreens::ACCOUNTLIST));

    // удаляем массив экранов по указателю
    delete &mapScreens;
}

void App::_startTransactionScreen() {
    // проверяем, нужно ли запускать другой экран
    if (m_storage.getState().intent_next_screen) {
        // если нужно, чекаем, слеудет ли сохранять текущий экран
        // в стэк
        if (m_storage.getState().is_push_stack) {
            // если да, то сохраняем текущий экран в стеке
            _pushStackCurrentScreen();

            // теперь обнуляем состояние помещения в стек
            // отправляем наше действие в диспач
            // данные оставляем пустыми
            // метод диспач у объекта store
            // принимает объект Action
            // этот объект содержит два поля: тип события
            // и данные
            // в данном случае, мы заполняем только тип
            // события, т к данные в нашем контексте не играют роли
            m_storage.dispatch(Action{
                    ActionTypes::CLEAR_PUSH_STACK_SCREEN
            });
        }

        // теперь нужно запустить новый экран, помещаем его в текущий
        // для этого мы берём у хранилища указатель на следующий экран
        // который был помещён туда предыдущим экраном
        // преобразовываем неопределённый указатель void
        // в указатель на новый экран
        // и кладём в текущий
        m_current_screen = static_cast<InterfaceScreen *>(m_storage.getState().intent_next_screen);

        // обнуляем указатель на следующий экран
        // отправляем действие в диспач
        // данные не заполняем
        m_storage.dispatch(Action{
                ActionTypes::CLEAR_INTENT_NEXT_SCREEN
        });
    } else {
        // если не нужно запускать другой экран
        // пытаемся получить прошлый экран из стэка
        if (bool err = _pullStackCurrentScreen(); !err) {
            // если стэк пуст, значит закрылся последний экран программы
            // придётся её закрыть
            m_is_run = false;
        }

        // если получили прошлый экран и заменили им текущий
        // значит всё хорошо
    }
}
