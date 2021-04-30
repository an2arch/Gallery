#ifndef PROJECT_PHOTO_H
#define PROJECT_PHOTO_H

#include <vector>
#include <Account.h>

using std::vector;

struct Photo {
    using PhotosList = vector<Photo *>;
    using Id = unsigned int;

    static Id current_photo_id;

    Id id{};
    Account::AccountsList marked_accounts{};
    string photo_path{};
};

std::ostream &operator<<(std::ostream &out, const Photo &photo);

#endif //PROJECT_PHOTO_H
