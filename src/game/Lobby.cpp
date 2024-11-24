/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier-test-ecs
** File description:
** Lobby
*/

/**
 * @file Lobby.cpp
 * @brief Lobby function
 * @version 0.1
 * @date 2022-10-17
 *
 */


#include "../../include/game/Lobby.hpp"
#include "server/Room.hpp"

Lobby_Serv::Lobby_Serv()
{
}

Lobby_Serv::~Lobby_Serv()
{
}

void Lobby_Serv::add_new_room(std::string name, int max_players)
{
    Room_server *room = new Room_server(name, max_players);
    rooms_on_list.push_back(room);
}

void Lobby_Serv::join_room(std::string name, s_Client cli)
{
    int i = 0;
    int index = 0;
    while (i != rooms_on_list.size()) {
        if (rooms_on_list.at(i)->room_name == name) {
            index = i;
        }
        i++;
    }
    //rooms_on_list.at(index)->Add_client();
    //surement dans un callback()
    //rooms_on_list.at(index)->Treating_Game_Loop();
}

void Lobby_Serv::destroy_room(std::string name)
{
    //for room name
    //if ok
    //rooms_on_list.erase();
}

Lobby_Client::Lobby_Client(std::vector<std::string> sended_names, std::vector<int16_t> sended_maxpl)
{
    names = sended_names;
    std::cout << sizeof(sended_names) << std::endl;
    max_players = sended_maxpl;
    std::cout << sizeof(sended_maxpl) << std::endl;
    join_room = 0;
    already_loaded = 0;
}

Lobby_Client::~Lobby_Client()
{
    UnloadTexture(Background);
    UnloadTexture(Lobby_button);
    UnloadTexture(Exit);
    UnloadTexture(Create_lobby);
}

void Lobby_Client::Lobby_page()
{
    if (already_loaded == 0) {
        Background = LoadTexture("assets/sprites/lobby_bg.png");
        Lobby_button = LoadTexture("assets/sprites/lobby_button.png");
        Exit = LoadTexture("assets/sprites/Exit.png");
        Create_lobby = LoadTexture("assets/sprites/Newgame.png");
        nbr_lobby = 0;
        Display();
    }
    else {
        Display();
    }
    already_loaded++;
}

void Lobby_Client::Display()
{
    cursor = GetMousePosition();

    btnActionNewgame = false;
    btnActionExit = false;

    btnStateNewgame = 0;
    btnStateExit = 0;

    frameHeightNewgame = (float)Create_lobby.height/3;
    sourceRecNewgame = { 0, 0, (float)Create_lobby.width, frameHeightNewgame };
    btnBoundsNewgame = { 350 - Create_lobby.width/2.0f, 500 - Create_lobby.height/3/2.0f, (float)Create_lobby.width, frameHeightNewgame };

    frameHeightExit = (float)Exit.height/3;
    sourceRecExit = { 0, 0, (float)Exit.width, frameHeightExit };
    btnBoundsExit = { 350 - Exit.width/2.0f, 800 - Exit.height/3/2.0f, (float)Exit.width, frameHeightExit };

    if (CheckCollisionPointRec(cursor, btnBoundsNewgame))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                btnStateNewgame = 2;

            }
            else btnStateNewgame = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                btnActionNewgame = true;
            }
        }
        else btnStateNewgame = 0;

    if (CheckCollisionPointRec(cursor, btnBoundsExit))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                btnStateExit = 2;
            else btnStateExit = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                btnActionExit = true;
        }
        else btnStateExit = 0;

    sourceRecNewgame.y = btnStateNewgame*frameHeightNewgame;

    sourceRecExit.y = btnStateExit*frameHeightExit;

    BeginDrawing();
    DrawTexture(Background, 0, 0, WHITE);

    DrawTextureRec(Create_lobby, sourceRecNewgame, (Vector2){ btnBoundsNewgame.x, btnBoundsNewgame.y }, WHITE); // Draw button frame

    DrawTextureRec(Exit, sourceRecExit, (Vector2){ btnBoundsExit.x, btnBoundsExit.y }, WHITE);

    for (int i = 0; i < names.size(); i++) {
        std::string max_player = "";
        nbr_lobby = i;
        max_player = std::to_string(max_players.at(i));
        DrawTexture(Lobby_button, 815, 115 + (nbr_lobby * 75), WHITE);
        DrawText(names.at(i).c_str(), 900, 145 + (nbr_lobby * 75), 30, BLACK);
        DrawText( max_player.c_str(), 1200, 145 + (nbr_lobby * 75), 30, BLACK);
        DrawText( " / 4", 1220, 145 + (nbr_lobby * 75), 30, BLACK);
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (cursor.x >= 815 && cursor.x <= 1920 && cursor.y >= 115 && cursor.y <= 190) {
            std::cout << "Room 1" << std::endl;
            SENDED_INFO.instruction = JOIN_ROOM;
            SENDED_INFO.name_selected = names.at(0);
        }
        if (cursor.x >= 815 && cursor.x <= 1920 && cursor.y >= 190 && cursor.y <= 265) {
            std::cout << "Room 2" << std::endl;
            SENDED_INFO.instruction = JOIN_ROOM;
            SENDED_INFO.name_selected = names.at(1);
        }
        if (cursor.x >= 815 && cursor.x <= 1920 && cursor.y >= 265 && cursor.y <= 340) {
            std::cout << "Room 3" << std::endl;
            SENDED_INFO.instruction = JOIN_ROOM;
            SENDED_INFO.name_selected = names.at(2);
        }
    }
    EndDrawing();
}
//dans le lobby_client
//join_room();
//send JOIN_ROOM INS

//serv JOIN_ROOM INS
//verif le nb player dedans à laide de la size des clients
//si c ok
//Lobby.join_room();
//send JOINED_ROOM

//client JOINED_ROOM
//