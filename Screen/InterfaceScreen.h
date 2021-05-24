#ifndef GALLERY_INTERFACESCREEN_H
#define GALLERY_INTERFACESCREEN_H

#include <Storage.h>
#include <config.h>
#include <map>
#include <stack>

class InterfaceScreen {
public:
    virtual int start() = 0;

    virtual void renderMain() const = 0;

    virtual ~InterfaceScreen() = default;
};

using MapScreens = std::map<IdScreens, InterfaceScreen *>;

using StackScreens = std::stack<InterfaceScreen *>;

#endif //GALLERY_INTERFACESCREEN_H
