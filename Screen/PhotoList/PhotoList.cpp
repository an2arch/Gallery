#include <PhotoList/PhotoList.h>

void PhotoList::_init() {
}

PhotoList::PhotoList() {
    _init();
}


PhotoList *PhotoList::createScreen() {
    static auto *photoList = new PhotoList{};
    return photoList;
}

int PhotoList::start() {
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

void PhotoList::renderMain() const {
    system("cls");
    cout << "Список фотографий\n";
    cout << "=================\n" << endl;

    printAllPhotos();
}

CMenu *PhotoList::createMenu() {
    PhotoList *photoList = createScreen();

    auto *menu = new CMenu{"Что вы хотите сделать?", ItemList{
            ItemMenu{"Отобразить все фотографии", [photoList]() -> int {
                photoList->printAllPhotos();
                return 0;
            }},
            ItemMenu{"Добавить фотографию", [photoList]() -> int {
                photoList->addNewPhoto();
                return 0;
            }},
            ItemMenu{"Редактировать фотографию", [photoList]() -> int {
                photoList->editPhoto();
                return 0;
            }},
            ItemMenu{"Удалить фотографию", [photoList]() -> int {
                photoList->deletePhoto();
                return 0;
            }},
            ItemMenu{"Вернуться назад", [photoList]() -> int {
                photoList->m_is_running = false;
                return 0;
            }}
    }};
    return menu;
}

void PhotoList::printAllPhotos() const {
    cout << "\nСписок всех фотографий\n"
         << "======================\n" << endl;

    cout << "Id\tPath\n"
         << "================\n" << endl;
    auto state = m_storage->getState();
    for (const auto &photo : state.photos) {
        cout << *photo << endl;
    }
    cout << "\n================\n" << endl;
}

void PhotoList::addNewPhoto() {
    cout << "\nДобавление новой фотографии\n";
    cout << "===========================\n" << endl;

    auto state = m_storage->getState();

    Photo newPhoto{};

    newPhoto.id = Photo::current_photo_id++;

    newPhoto.photo_path = tool::getEnteredString("Введите путь до фотографии -> ");

    AccountList *accountList = AccountList::createScreen();
    accountList->printAccountList(nullptr, [](const auto &account) -> bool {
        return account->level_access == Account::LevelAccess::User;
    });

    newPhoto.marked_accounts = _getMarkedAccounts();

    m_storage->dispatch(Action{
            ActionTypes::ADD_NEW_PHOTO,
            &newPhoto
    });

    cout << "\nФотография успешно добавлена\n";
    cout << "============================\n" << endl;
}

void PhotoList::editPhoto() {
    cout << "\nРедактирование фотографии\n"
         << "=========================\n" << endl;
    printAllPhotos();

    auto state = m_storage->getState();
    Photo editPhoto{};

    editPhoto.id = tool::getEnteredNum(
            "Введите id нужной фотографии -> ",
            [&state](int entered) -> bool {
                return std::any_of(state.photos.begin(), state.photos.end(),
                                   [entered](const auto &photo) -> bool {
                                       return entered == photo->id;
                                   });
            });

    editPhoto.photo_path = tool::getEnteredString("Введите новый путь к фотографии -> ");

    editPhoto.marked_accounts = _getMarkedAccounts();

    m_storage->dispatch(Action{
            ActionTypes::EDIT_PHOTO,
            &editPhoto
    });

    cout << "\nФотография успешно отредактирована\n"
         << "==================================\n" << endl;
}

void PhotoList::deletePhoto() {
    cout << "\nУдаление фотографии\n"
         << "===================\n" << endl;

    printAllPhotos();

    auto state = m_storage->getState();

    size_t photoIdToDelete = tool::getEnteredNum(
            "Введите id фотографии -> ",
            [&state](int id) -> bool {
                return std::any_of(state.photos.begin(), state.photos.end(),
                                   [id](const auto &photo) -> bool {
                                       return id == photo->id;
                                   });
            });

    size_t indexPhoto{};

    for (const auto &photo : state.photos) {
        if (photo->id == photoIdToDelete) {
            break;
        }
        ++indexPhoto;
    }

    m_storage->dispatch(Action{
            ActionTypes::DELETE_PHOTO,
            &indexPhoto
    });

    cout << "\nФотография успешно удалёна\n"
         << "======================\n" << endl;
}

Account::AccountsList PhotoList::_getMarkedAccounts() {
    auto state = m_storage->getState();
    Account::AccountsList marked_accounts{};
    vector<int> markedAccountsId = tool::getEnteredInts(
            "Введите Id отмеченных пользователей -> ",
            [&state](int entered) -> bool {
                return std::any_of(state.accounts.begin(),
                                   state.accounts.end(),
                                   [entered](const auto &account) -> bool {
                                       return account->id == entered;
                                   });
            });

    for (const auto &id : markedAccountsId) {
        auto user = std::find_if(state.accounts.begin(), state.accounts.end(), [id](const auto &account) -> bool {
            return account->id == id;
        });
        marked_accounts.push_back(*user);
    }
    return marked_accounts;
}
