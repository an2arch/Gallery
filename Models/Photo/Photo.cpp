#include "Photo.h"

Photo::Id Photo::current_photo_id{};

std::ostream &operator<<(std::ostream &out, const Photo &photo) {
    out << photo.id << "\t"
        << photo.photo_path << "\t";
    for (const auto &markedUser : photo.marked_accounts) {
        cout << markedUser->name << " ";
    }
    return out;
}
