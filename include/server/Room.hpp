/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier-test-ecs
** File description:
** Room
*/

#include <iostream>
#include <vector>
#include "ServerInternalLogic.hpp"
#include "ClientInternalLogic.hpp"
#include <boost/asio.hpp>
using boost::asio::ip::udp;
#ifndef ROOM_HPP_
#define ROOM_HPP_

class Room_server {
    public:
        Room_server(std::string name, int max_players);
        ~Room_server();
        void Create_room(udp::endpoint _sender_endpoint, int index);
        void Add_client(udp::endpoint _sender_endpoint);
        void Treating_Game_Loop(int type, int pos_x, int pos_y, int id);
        std::vector<udp::endpoint> clients_in_game;
        std::vector<s_Entity> players;
        std::string room_name;
        std::vector<std::string> levels;
        int16_t max_players;
        ServerInternalLogic *Game;
        int lose;
        int index_level;
        int change_level;
        bool hasPlayedYet;
    protected:
    private:
};

class Room_client {
    public:
        Room_client(std::vector<s_Entity> Original_RAM, int id); //créer le cache etc...;
        ~Room_client();
        void Room_read_from_server(std::vector<s_Entity> New_RAM, int new_id); // avec verif cache
        ClientInternalLogic *Renders;
    protected:
    private:
};

#endif /* !ROOM_HPP_ */
