/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** centipede
*/

#include "centipede.hpp"

IGame *game = nullptr;

__attribute__((constructor)) void load_lib()
{
    game = new centipede;
}

// __attribute__((destructor)) void unload_lib()
// {
// }

extern "C" IGame *entry_point()
{
    return (game);
}

centipede::centipede()
{

}

centipede::~centipede()
{

}

void centipede::loop(ILib *lib)
{
    std::string s = "centipede";

    while (1) {
        lib->erasew();
        lib->print(10, 10, s);
        lib->refreshw();
    }
}