

/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier
** File description:
** fire.hpp
*/

/**
 * @file Fire.cpp
 * @brief Fire class
 * @version 0.1
 * @date 2022-10-17
 *
 */

#include "raylib.h"
#include <iostream>

class fire
{
private:

public:
    Texture2D bullet;
    const char *texture;
    Vector2 bulletPos;
    bool bulletActive;
    fire::fire(const char *texture, Vector2 bulletPos, bool bulletActive)
    {
        bullet = LoadTexture(texture);
        bulletActive = true;
        bulletPos = (Vector2){bulletPos.x , bulletPos.y};
    }

    fire::~fire()
    {
        bulletActive = false;
        UnloadTexture(bullet);
    }
};

