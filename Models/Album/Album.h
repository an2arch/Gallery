#ifndef PROJECT_ALBUM_H
#define PROJECT_ALBUM_H

#include <Photo.h>
#include <string>
#include <vector>
#include <ostream>

using std::string;
using std::vector;

struct Album {
    using AlbumsList = vector<Album *>;
    using Id = unsigned int;
    static Id current_album_id;
    Id id{};
    string name{};
    Photo::PhotosList photos{};
    Account *owner{};
};

std::ostream &operator<<(std::ostream &out, const Album &album);


#endif //PROJECT_ALBUM_H
