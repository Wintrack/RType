/*
** EPITECH PROJECT, 2022
** re_encore_une_version_r-type
** File description:
** s_Entity.hpp
*/

#ifndef S_ENTITY
#define S_ENTITY

#include "raylib.h"

struct c_Entity
{
    int type;
    int underType;
    int id;
    int health;
    int pos_y; // modif par 
    int pos_x;
    int frame;         // get_update()
    int damage;   // if (On_screen == false)  {
    Texture2D sprite; // int id_to_kill = disp.at().id
    int i_frame;      // display.at(..).~destructor
    bool hasPLayed;   // display.erase
                       // while (cache id != id_to_erase)
                       // } ... souvenir de lindex puis erase du cache
};

#endif