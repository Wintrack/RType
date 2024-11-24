/*
** EPITECH PROJECT, 2022
** TEK3
** File description:
** Macro
*/

/**
 * @file Macro.hpp
 * @brief Macro
 * @version 0.1
 * @date 2022-10-17
 *
 */


#pragma once

#include <iostream>
#include <vector>
#include "Entity.hpp"

#define STARSHIP "assets/sprites/starship.png"
#define BACKGROUND "assets/sprites/Background.png"
#define BULLET  "assets/sprites/bulletv1.png"
#define BADDUDE "assets/sprites/enemy1.png"

#define JOIN_LOBBY_INS 0
#define EXIT_CLIENT_INS 9
#define CREATE_ROOM_INS 2
#define JOIN_ROOM 3
#define RETURN_INS 4
#define JOIN_GAME 8
//
#define JOINED_LOBBY 5
#define JOINED_ROOM 6
#define JOINED_GAME 7


#define CHAMP_DELIMITER -1
#define VAR_DELIMITER -2
#define END_DATA -3

struct s_Client
{
    int IP;
    int Port;
};

//Client envoit ceci avec l'Ins JOIN_ROOM
//CREATE_ROOM
struct INSTRUCTION_CREATE_ROOM_Client {
    int instruction;
    std::string name_room;
    int maxplay;
};

struct INSTRUCTION_JOIN_LOBBY_Serv {
    int instruction;
    std::vector<std::string> rooms_in_lobby;
    std::vector<int> maxpl;
};

struct INSTRUCTION_JOIN_ROOM_Client {
    int instruction;
    std::string name;
    s_Client client;
};

struct INSTRUCTION_GENERIC {
    int instruction;
    std::vector<std::string> rooms_in_lobby;
    std::vector<int16_t> maxpl;
    std::string name_room_created;
    std::string name_selected;
    std::vector<s_Entity> RAM_DATABASE;
    std::vector<int16_t> info_player;
};


//IN GAME
struct INSTRUCTION_Serv_to_Client_room {
};


//champ dans le vec info_player
struct INSTRUCTION_Client_in_room {
    int type; // soit un 
    int pos_x;
    int pos_y;
    int id;
};
