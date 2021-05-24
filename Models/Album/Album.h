#ifndef GALLERY_ALBUM_H
#define GALLERY_ALBUM_H

#include <Photo.h>
#include <string>
#include <ostream>
#include <memory>

#include <vector>

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
        archive(
                CEREAL_NVP(name),
                CEREAL_NVP(id),
                CEREAL_NVP(photos),
                CEREAL_NVP(owner)
        );
    }
};

std::ostream &operator<<(std::ostream &out, const Album &album);


#endif //GALLERY_ALBUM_H
