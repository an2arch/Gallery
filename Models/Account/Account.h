#ifndef PROJECT_ACCOUNT_H
#define PROJECT_ACCOUNT_H

#include <string>
#include <vector>
#include <ostream>
#include <iomanip>
#include <Utility.h>

using std::string;
using std::vector;

struct Account {
    using AccountsList = vector<Account *>;

    enum class LevelAccess : short {
        Admin,
        User
    };

    using Id = unsigned int;

    static Id current_user_id;

    string name{};
    Id id{};
    string login{};
    string password{};
    LevelAccess level_access{};
};

std::ostream &operator<<(std::ostream &out, const Account &acc);


#endif //PROJECT_ACCOUNT_H
