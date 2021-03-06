#ifndef GALLERY_ALBUM_LIST_H
#define GALLERY_ALBUM_LIST_H

#include <functional>
#include <Album.h>
#include <Storage.h>
#include <InterfaceScreen.h>
#include <CMenu.h>
#include <TablePrint/TablePrint.h>

using std::function;
using std::cin;
using std::cout;
using std::endl;

class AlbumList : public InterfaceScreen {
public:
    using SortOrderFunction = function<bool(const shared_ptr<Album> &, const shared_ptr<Album> &)>;

    AlbumList(const AlbumList &) = delete;

    AlbumList &operator=(const AlbumList &) = delete;

    static AlbumList *createScreen();

    int start() override;

    void renderMain() const override;

    CMenu *createMenu();

    void addNewAlbum();

    void editAlbum();

    void deleteAlbum();

    void sortAlbumsByName() const;

    void printAlbums(const SortOrderFunction &sortOrderFunc = nullptr) const;

    void printAllAlbums() const;

private:
    AlbumList();

    Storage *m_storage{};
    bool m_is_running{};

    void _init();

    Photo::PhotosList
    _getPhotos(const string &text, const tool::ValidateNum &validate = nullptr, std::istream &in = std::cin) const;
};


#endif //GALLERY_ALBUM_LIST_H
