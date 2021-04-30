#include "Account.h"

Account::Id Account::current_user_id{};

std::ostream &operator<<(std::ostream &out, const Account &acc) {
    out << acc.id << "\t"
        << acc.name << "\t"
        << acc.login << "\t"
        << acc.password << "\t"
        << (acc.level_access == Account::LevelAccess::Admin ? "Admin" : "User");
    return out;
}
