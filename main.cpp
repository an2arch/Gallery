#include <App.h>

int main() {
    // обращаемся к статическому методу класса App
    // класс App - это контейнер всего приложения
    // который управлять экранами программы
    // App - является объектом синглтоном
    // т е на протяжении всей работы программы
    // в памяти существует только один его
    // статический объект
    // метод createApp при первом вызове создаёт
    // и возвращает новый статический объект App
    // на который мы создаём ссылку
    App &app = App::createApp();

    // дальше, у созданного объекта мы
    // вызываем метод start, который запускает главный цикл
    // обработки запросов нашего приложения
    // на выходе метод возвращает код возврата ошибки
    // по этому мы сразу возвращаем этот код возврата ошшибки
    // через return
    return app.start();
}
