#ifndef PROJECT_ALBUM_H
#define PROJECT_ALBUM_H

#include <Photo.h>
#include <string>
#include <vector>
#include <ostream>
#include <memory>

#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>

using std::string;
using std::vector;
using std::shared_ptr;

struct Album {
    using AlbumsList = vector<shared_ptr<Album>>;
    using Id = unsigned int;
    static Id current_album_id;
    Id id{};
    string name{};
    Photo::PhotosList photos{};
    shared_ptr<Account> owner{};

    template<class Archive>
    void serialize(Archive &archive) {
        archive(CEREAL_NVP_("name", name),
                CEREAL_NVP_("id", id),
                CEREAL_NVP_("login", photos),
                CEREAL_NVP_("password", owner));
    }
};

std::ostream &operator<<(std::ostream &out, const Album &album);


#endif //PROJECT_ALBUM_H
