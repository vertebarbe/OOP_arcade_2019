/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** dlHandler
*/

#include "dlHandler.hpp"

typedef ILib *(*entry_point)();

void dlHandler::loadLib(std::string path)
{
    if (_handle != nullptr)
        unLoadLib();
    path = "./" + path;
    _handle = dlopen(path.c_str(), RTLD_LAZY);
    if (_handle == nullptr)
        std::cerr << dlerror() << std::endl;
}

void dlHandler::unLoadLib()
{
    dlclose(_handle);
}

ILib *dlHandler::getLib() const
{
    ILib *lib = nullptr;
    void *tmp = nullptr;
    entry_point entry;
    if (_handle == nullptr) {
        std::cerr << "No lib has been loaded yet" << std::endl;
        return (nullptr);
    }
    tmp = dlsym(_handle, "entry_point");
    if (tmp == nullptr) {
        std::cerr << "Could not get Lib Class" << std::endl;
        return (nullptr);
    }
    entry = (entry_point)tmp;
    lib = entry();
    return (lib);
}