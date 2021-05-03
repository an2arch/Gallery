#include "Account.h"

Account::Id Account::current_user_id{};

std::ostream &operator<<(std::ostream &out, const Account::LevelAccess &level_access) {
    out << (level_access == Account::LevelAccess::Admin ? "Admin" : "User");
    return out;
}
