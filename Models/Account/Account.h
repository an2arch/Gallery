#ifndef GALLERY_ACCOUNT_H
#define GALLERY_ACCOUNT_H

#include <string>
#include <vector>
#include <ostream>
#include <iomanip>
#include <memory>

#include <vector>

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
        archive(
                CEREAL_NVP(name),
                CEREAL_NVP(id),
                CEREAL_NVP(login),
                CEREAL_NVP(password),
                CEREAL_NVP(level_access)
        );
    }
};

std::ostream &operator<<(std::ostream &out, const Account::LevelAccess &level_access);


#endif //GALLERY_ACCOUNT_H
