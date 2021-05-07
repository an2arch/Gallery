#ifndef PROJECT_ALBUMLIST_H
#define PROJECT_ALBUMLIST_H

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

    void _init();

    Photo::PhotosList _getPhotos();

    Storage *m_storage{};
    bool m_is_running{};
};


#endif //PROJECT_ALBUMLIST_H
