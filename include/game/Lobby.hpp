/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier-test-ecs
** File description:
** Lobby
*/

/**
 * @file Lobby.hpp
 * @brief Lobby class
 * @version 0.1
 * @date 2022-10-17
 *
 */


#include <iostream>
#include <vector>
#include "../server/Room.hpp"
#include "Macro.hpp"
#include "raylib.h"

#ifndef LOBBY_HPP_
#define LOBBY_HPP_

class Lobby_Serv {
    public:
        Lobby_Serv();
        ~Lobby_Serv();
        void add_new_room(std::string name, int max_players);
        void join_room(std::string name, s_Client cli);
        void destroy_room(std::string name);
        std::vector<Room_server *> rooms_on_list;
    protected:
    private:
};

class Lobby_Client {
public:
        Texture2D Background;
        Texture2D Lobby_button;
        Texture2D Exit;
        Texture2D Create_lobby;

        int join_looby;
        int already_checked;
        float frameHeightNewgame;
        Rectangle sourceRecNewgame;
        Rectangle btnBoundsNewgame;

        float frameHeightExit;
        Rectangle sourceRecExit;
        Rectangle btnBoundsExit;
        Vector2 cursor;
        int btnStateNewgame;
        bool btnActionNewgame;

        int btnStateExit;
        bool btnActionExit;

        Lobby_Client(std::vector<std::string> sended_names, std::vector<int16_t> players_by_map);
        ~Lobby_Client();
        void Lobby_page();
        void Display();
        int join_room;
        int already_loaded;
        int nbr_lobby = 0;
        INSTRUCTION_GENERIC SENDED_INFO;
    protected:
    private:
        std::vector<std::string> names;
        std::vector<int16_t> max_players;
        std::vector<Room_client *> Joinable_rooms;
};

#endif /* !LOBBY_HPP_ */
