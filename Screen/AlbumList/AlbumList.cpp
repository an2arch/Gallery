#include "AlbumList.h"

void AlbumList::_init() {
}

AlbumList::AlbumList() {
    _init();
}

Photo::PhotosList AlbumList::_getPhotos() {
    return Photo::PhotosList();
}

AlbumList *AlbumList::createScreen() {
    static auto *albumList = new AlbumList{};
    return albumList;
}

int AlbumList::start() {
    m_storage = Storage::getStorage();
    renderMain();
    CMenu &menu = *createMenu();
    m_is_running = true;
    while (m_is_running) {
        cout << menu;
        cin >> menu;
        menu();
    }
    delete &menu;
    return 0;
}

void AlbumList::renderMain() const {
    system("cls");
    cout << "Список всех альбомов\n";
    cout << "=========================\n" << endl;
    printAllAlbums();
}

CMenu *AlbumList::createMenu() {
    AlbumList *accountList = AlbumList::createScreen();
    auto *menu = new CMenu{"Что бы вы хотели сделать?", ItemList{
            ItemMenu{"Отобразить все альбомы", [accountList]() -> int {
                accountList->printAllAlbums();
                return 1;
            }},
            ItemMenu{"Добавить новый альбом", [accountList]() -> int {
                accountList->addNewAlbum();
                return 2;
            }},
            ItemMenu{"Редактировать альбом", [accountList]() -> int {
                accountList->editAlbum();
                return 3;
            }},
            ItemMenu{"Удалить альбом", [accountList]() -> int {
                accountList->deleteAlbum();
                return 4;
            }},
            ItemMenu{"Сортировка альбомов по названию", [accountList]() -> int {
                accountList->sortAlbumsByName();
                return 5;
            }},
            ItemMenu{"Вернуться назад", [accountList]() -> int {
                accountList->m_is_running = false;
                return 6;
            }},
    }};
    return menu;
}

void AlbumList::addNewAlbum() {
    cout << "\nДобавление нового альбома\n";
    cout << "===========================\n" << endl;

    auto state = m_storage->getState();

    Album newAlbum{};

    newAlbum.id = Album::current_album_id++;
    newAlbum.name = tool::getEnteredString("Введите название альбома -> ");
    newAlbum.owner = std::make_shared<Account>(*state.current_user);
    newAlbum.photos = _getPhotos();

    m_storage->dispatch(Action{
            ActionTypes::ADD_NEW_ALBUM,
            &newAlbum
    });

    cout << "\nАльбом успешно добавлен\n"
         << "===========================\n" << endl;
}

void AlbumList::editAlbum() {
    cout << "\nРедактирование альбома\n"
         << "=========================\n" << endl;
    printAllAlbums();

    auto state = m_storage->getState();
    Album editAlbum{};

    editAlbum.id = tool::getEnteredNum(
            "Введите id нужного альбома -> ",
            [state](int entered) -> bool {
                return std::any_of(state.albums.begin(), state.albums.end(),
                                   [entered](const auto &album) -> bool {
                                       return entered == album->id;
                                   });
            });

    editAlbum.name = tool::getEnteredString("Введите новое название альбома -> ");

    editAlbum.photos = _getPhotos();

    editAlbum.owner = std::make_shared<Account>(*state.current_user);

    m_storage->dispatch(Action{
            ActionTypes::EDIT_ALBUM,
            &editAlbum
    });

    cout << "\nАльбом успешно отредактирован\n"
         << "==================================\n" << endl;
}

void AlbumList::deleteAlbum() {
    cout << "\nУдаление альбома\n"
         << "===================\n" << endl;

    printAllAlbums();

    auto state = m_storage->getState();

    size_t albumIdToDelete = tool::getEnteredNum(
            "Введите id альбома -> ",
            [state](int id) -> bool {
                return std::any_of(state.albums.begin(), state.albums.end(),
                                   [id, state](const auto &album) -> bool {
                                       return id == album->id;
                                   });
            });

    size_t indexAlbum{};

    for (const auto &album: state.albums) {
        if (album->id == albumIdToDelete) {
            break;
        }
        ++indexAlbum;
    }

    m_storage->dispatch(Action{
            ActionTypes::DELETE_ALBUM,
            &indexAlbum
    });

    cout << "\nАльбом успешно удалён\n"
         << "======================\n" << endl;
}

void AlbumList::sortAlbumsByName() const {
    cout << "\nСортировка альбомов по названию\n"
         << "===============================\n" << endl;

    printAlbums([](const auto &first, const auto &second) -> bool {
        return first->name < second->name;
    });

    cout << "===============================\n" << endl;
}

void AlbumList::printAlbums(const AlbumList::SortOrderFunction &sortOrderFunc) const {
    auto albumsList = m_storage->getState().albums;

    Album::AlbumsList newAlbumsList{albumsList};

    if (sortOrderFunc) {
        newAlbumsList = tool::sort(newAlbumsList, sortOrderFunc);
    }

    cout << "Id\tНазвание\tВладелец\n";
    cout << "==================================\n" << endl;

    for (const auto &album : newAlbumsList) {
        cout << *album << endl;
    }
    cout << "==================================\n" << endl;
}

void AlbumList::printAllAlbums() const {
    cout << "\nСписок альбомов\n"
         << "===========\n" << endl;
    printAlbums();
}
