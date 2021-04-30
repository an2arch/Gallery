#include "Album.h"

Album::Id Album::current_album_id{};

std::ostream &operator<<(std::ostream &out, const Album &album) {
    out << album.id << "\t"
        << album.name << "\t"
        << album.owner->name;
    return out;
}
