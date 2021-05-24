#ifndef GALLERY__TABLEPRINT_H
#define GALLERY__TABLEPRINT_H

#include <numeric>
#include <map>
#include <iostream>
#include <iomanip>
#include <Account/Account.h>
#include <Photo/Photo.h>
#include <Album/Album.h>

namespace tool {
    void printTable(const Account::AccountsList &list, std::ostream &out = std::cout);

    void printTable(const Photo::PhotosList &list, std::ostream &out = std::cout);

    void printTable(const Album::AlbumsList &list, std::ostream &out = std::cout);
}

#endif //GALLERY__TABLEPRINT_H
