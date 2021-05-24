#include <App.h>
#include <exception>

int main() {
    try {
        App &app = App::createApp();
        return app.start();
    } catch (std::exception &error) {
        std::cerr << "Some error occurred!\nwhat(): " << error.what() << std::endl;
        std::cerr << "Aborting program execution...." << std::endl;
        exit(1);
    }
}
