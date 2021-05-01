#ifndef PROJECT_ACCOUNT_H
#define PROJECT_ACCOUNT_H

#include <string>
#include <vector>
#include <ostream>
#include <iomanip>
#include <Utility.h>
#include <memory>

#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>

using std::string;
using std::vector;
using std::shared_ptr;

struct Account {
    using AccountsList = vector<shared_ptr<Account>>;

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

    template<class Archive>
    void serialize(Archive &archive) {
        archive(CEREAL_NVP_("name", name),
                CEREAL_NVP_("id", id),
                CEREAL_NVP_("login", login),
                CEREAL_NVP_("password", password),
                CEREAL_NVP_("level_access", level_access));
    }
};

std::ostream &operator<<(std::ostream &out, const Account &acc);


#endif //PROJECT_ACCOUNT_H
