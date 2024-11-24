/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier
** File description:
** Game.hpp
*/

/**
 * @file Game.cpp
 * @brief Game class
 * @version 0.1
 * @date 2022-10-17
 *
 */


#pragma once
#include <cstdint.hpp>
#include <fire.hpp>

class Game
{
private:
    /* data */
public:
    Game(/* args */);
    ~Game();
    std::int8_t getInput();
    int gameLoop();
};

