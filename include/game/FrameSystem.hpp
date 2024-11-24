/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** FrameSysteme
*/

#pragma once

#include <string.h>
#include "game/Macro.hpp"
#include "Entity.hpp"

#include "raylib.h"

class FrameSystem
{
public:
    FrameSystem(s_Entity entity) {
        _entity = entity;
        _pos = {90, 90};
        _pos_bullet = {32, 10};
        _frameRec = {0.0f, 0.0f, (float)_texture.width/5, (float)_texture.height};
    };
    ~FrameSystem();

    void loadInGameTexture()
    {
        switch (_entity.id)
        {
        case 1:
            _texture = LoadTexture(STARSHIP);
            break;
        case 2:
            _texture = LoadTexture(BADDUDE);
            break;
        case 4:
            _texture = LoadTexture(BULLET)
            break;
        default:
            break;
        }
    };
    void displayFrame() {
        _frameRec.x = (float)_entity.frame*(float)_texture.width/5;
        ClearBackground(BLACK);
        if (_texture.id == 4)
            DrawTextureRec(_texture, _frameRecBullet, _pos, WHITE);
        else
            DrawTextureRec(_texture, _frameRec, _pos, WHITE);
    };

private:
    Texture2D _texture;
    Rectangle _frameRec;
    Rectangle _frameRecBullet;
    s_Entity _entity;

    Vector2 _pos_bullet;
    Vector2 _pos;
};

/*
1 = player
2 = ennemi
4 = bullet
5 = block
*/