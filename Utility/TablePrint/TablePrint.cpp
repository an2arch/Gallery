#include "TablePrint.h"

namespace tool {
    void printTable(const Account::AccountsList &list, std::ostream &out) {
        std::map<string, size_t> offsets{
                {"id",           0},
                {"name",         0},
                {"login",        0},
                {"password",     0},
                {"level_access", 13}
        };

        for (const auto &account : list) {
            offsets["id"] = std::max(offsets["id"], std::to_string(account->id).length());
            offsets["name"] = std::max(offsets["name"], account->name.length());
            offsets["login"] = std::max(offsets["login"], account->login.length());
            offsets["password"] = std::max(offsets["password"], account->password.length());
        }

        for (auto &element : offsets) {
            element.second = std::max(element.second, element.first.length()) + 2;
        }

        out << std::setw(offsets["id"]) << "Id";
        out << std::setw(offsets["name"]) << "Name";
        out << std::setw(offsets["login"]) << "Login";
        out << std::setw(offsets["password"]) << "Password";
        out << std::setw(offsets["level_access"]) << "Level access";

        out << "\n====================================================================\n\n";

        for (const auto &account : list) {
            out << std::setw(offsets["id"]) << account->id
                << std::setw(offsets["name"]) << account->name
                << std::setw(offsets["login"]) << account->login
                << std::setw(offsets["password"]) << account->password
                << std::setw(offsets["level_access"]) << account->level_access;
            out << std::endl;
        }
        out << "====================================================================\n\n";
    }

    void printTable(const Photo::PhotosList &list, std::ostream &out) {
        std::map<string, size_t> offsets{
                {"id",              0},
                {"photo_path",      0},
                {"marked_accounts", 0}
        };

        for (const auto &photo: list) {
            offsets["id"] = std::max(offsets["id"], std::to_string(photo->id).length());
            offsets["photo_path"] = std::max(offsets["photo_path"], photo->photo_path.length());
            std::string allMarked{
                    std::accumulate(photo->marked_accounts.begin(),
                                    photo->marked_accounts.end(),
                                    std::string{},
                                    [](const string &acc, const auto &account) -> std::string {
                                        return acc + account->name + " ";
                                    })};
            offsets["marked_accounts"] = std::max(offsets["marked_accounts"], allMarked.length());
        }

        for (auto &element : offsets) {
            element.second = std::max(element.second, element.first.length()) + 2;
        }

        out << std::setw(offsets["id"]) << "Id";
        out << std::setw(offsets["photo_path"]) << "Photo path";
        out << std::setw(offsets["marked_accounts"]) << "Marked accounts";

        out << "\n====================================================================\n\n";

        for (const auto &photo : list) {
            std::string allMarked{
                    std::accumulate(photo->marked_accounts.begin(),
                                    photo->marked_accounts.end(),
                                    std::string{},
                                    [](const string &acc, const auto &account) -> string {
                                        return acc + " " + account->name;
                                    })};
            out << std::setw(offsets["id"]) << photo->id
                << std::setw(offsets["photo_path"]) << photo->photo_path
                << std::setw(offsets["marked_accounts"]) << allMarked;
            out << std::endl;
        }

        out << "====================================================================\n\n";
    }

    void printTable(const Album::AlbumsList &list, std::ostream &out) {
        std::map<string, size_t> offsets{
                {"id",     0},
                {"name",   0},
                {"owner",  0},
                {"photos", 0}
        };

        for (const auto &album: list) {
            offsets["id"] = std::max(offsets["id"], std::to_string(album->id).length());
            offsets["name"] = std::max(offsets["name"], album->name.length());
            offsets["owner"] = std::max(offsets["owner"], album->owner->name.length());
            std::string allPhotos{
                    std::accumulate(album->photos.begin(),
                                    album->photos.end(),
                                    std::string{},
                                    [](const string &acc, const auto &photo) -> std::string {
                                        return acc + std::to_string(photo->id) + " ";
                                    })};
            offsets["photos"] = std::max(offsets["photos"], allPhotos.length());
        }

        for (auto &element : offsets) {
            element.second = std::max(element.second, element.first.length()) + 2;
        }

        out << std::setw(offsets["id"]) << "Id";
        out << std::setw(offsets["name"]) << "Name";
        out << std::setw(offsets["owner"]) << "Owner";
        out << std::setw(offsets["photos"]) << "Photos";

        out << "\n====================================================================\n\n";

        for (const auto &album : list) {
            std::string allPhotos{
                    std::accumulate(album->photos.begin(),
                                    album->photos.end(),
                                    std::string{},
                                    [](const string &acc, const auto &photo) -> std::string {
                                        return acc + std::to_string(photo->id) + " ";
                                    })};
            out << std::setw(offsets["id"]) << album->id
                << std::setw(offsets["name"]) << album->name
                << std::setw(offsets["owner"]) << album->owner->name
                << std::setw(offsets["photos"]) << allPhotos;
            out << std::endl;
        }

        out << "====================================================================\n\n";
    }
}
