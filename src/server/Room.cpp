/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier-test-ecs
** File description:
** Room
*/

/**
 * @file Room.cpp
 * @brief Room class
 * @version 0.1
 * @date 2022-10-17
 *
 */


#include "../../include/server/Room.hpp"


Room_server::Room_server(std::string name, int max_pl)
{
    room_name = name;
    max_players = max_pl;
    lose = 0;
    change_level = 0;
    index_level = 0;
    hasPlayedYet = false;
    levels.push_back("map1.txt");
    levels.push_back("map2.txt");
    levels.push_back("map3.txt");
}

Room_server::~Room_server()
{
    clients_in_game.clear();
    Game->~ServerInternalLogic();
}

void Room_server::Create_room(udp::endpoint _sender_endpoint, int index)
{
    clients_in_game.push_back(_sender_endpoint);
    Game = new ServerInternalLogic(levels.at(index));
}

void Room_server::Add_client(udp::endpoint _sender_endpoint)
{
    clients_in_game.push_back(_sender_endpoint);
    Game->Add_new_player();
}

void Room_server::Treating_Game_Loop(int type, int pos_x, int pos_y, int id)
{
    int boss_clear = 0;
    players.clear();
    for (int i = 0; i != Game->DATABASE.size(); i++) {
        if(Game->DATABASE.at(i)->getStruc()->type == 1 && Game->DATABASE.at(i)->getStruc()->health > 0) {
            players.push_back(*Game->DATABASE.at(i)->getStruc());
            std::cout << "IM A PLAYER" << std::endl;
        }
        if(Game->DATABASE.at(i)->getStruc()->type == 6) {
            boss_clear++;
        }
    }
    if (players.size() > 0) {
        Game->Receive_from_client(type, pos_x, pos_y, id);
        std::cout << "_________________________AVANT CALL ASYNCRO CALC___________________" << std::endl;
        Game->Asynchronic_Calculation();
        hasPlayedYet = true;
    }
    if (players.size() <= 0) {
        lose++;
        hasPlayedYet = false;
    }
    if (boss_clear == 0) {
        change_level++;
        index_level++;
    }
}


Room_client::Room_client(std::vector<s_Entity> Original_RAM, int id)
{
    Renders = new ClientInternalLogic(Original_RAM, id);
}

Room_client::~Room_client()
{
}

void Room_client::Room_read_from_server(std::vector<s_Entity> New_RAM, int new_id)
{
    Renders->Verify_Cache(New_RAM);
    Renders->Client_Display(new_id);

}