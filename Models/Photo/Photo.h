#ifndef PROJECT_PHOTO_H
#define PROJECT_PHOTO_H

#include <vector>
#include <memory>
#include <Account.h>

#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>

using std::vector;
using std::shared_ptr;

struct Photo {
    using PhotosList = vector<shared_ptr<Photo>>;
    using Id = unsigned int;

    static Id current_photo_id;

    Id id{};
    Account::AccountsList marked_accounts{};
    string photo_path{};

    template<class Archive>
    void serialize(Archive &archive) {
        archive(marked_accounts, id, photo_path);
    }
};

std::ostream &operator<<(std::ostream &out, const Photo &photo);

#endif //PROJECT_PHOTO_H
