#include <Utility.h>

namespace tool {
    string getEnteredString(const string &text, const ValidateString &validate, std::istream &in) {
        string console_enter{};

        while (true) {
            cout << text;
            in >> console_enter;

            if (in.fail() || (validate && !validate(console_enter))) {
                console_enter.clear();
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\n\nYou entered an incorrect value, please try again!\n\n";
                continue;
            }

            break;
        }

        return console_enter;
    }

    int getEnteredNum(const string &text, const ValidateNum &validate, std::istream &in) {
        int console_enter{};

        while (true) {
            cout << text;
            in >> console_enter;

            if (cin.fail() || (validate && !validate(console_enter))) {
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\n\nYou entered an incorrect value, please try again!\n\n";
                continue;
            }

            break;
        }

        return console_enter;
    }

    char getEnteredChar(const string &text, const ValidateChar &validate, std::istream &in) {
        char console_enter{};

        while (true) {
            cout << text;
            in >> console_enter;

            if (cin.fail() || (validate && !validate(console_enter))) {
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "\n\nYou entered an incorrect value, please try again!\n\n";
                continue;
            }

            break;
        }

        return console_enter;
    }

    vector<int> getEnteredInts(const string &text, const ValidateNum &validate, std::istream &in) {
        vector<int> entered{};

        bool fail{};

        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        while (true) {
            fail = false;
            string line{};
            cout << text;
            std::getline(in, line, '\n');
            istringstream ss{line};

            int tmp{};
            while (ss >> tmp && !fail) {
                if (ss.fail() || (validate && !validate(tmp))) {
                    ss.clear();
                    ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    entered.clear();
                    cout << "\n\nYou entered an incorrect value, please try again!\n\n";
                    fail = true;
                    continue;
                }
                entered.push_back(tmp);
            }
            if (ss.get() && !fail) {
                break;
            }
        }
        return entered;
    }

    void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
        system("cls");
#else
        system("clear");
#endif
    }
}
