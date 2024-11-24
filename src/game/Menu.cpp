/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier-test-ecs
** File description:
** Menu
*/

/**
 * @file Menu.cpp
 * @brief Menu function
 * @version 0.1
 * @date 2022-10-17
 *
 */


#include "game/Menu.hpp"
#include "raylib.h"
#include <boost/asio.hpp>

using boost::asio::ip::udp;

Menu::Menu()
{
    already_checked = 0;
}

void Menu::Display()
{
    cursor = GetMousePosition();
        btnActionNewgame = false;
        btnActionSettings = false;
        btnActionExit = false;
        btnActionSolo = false;

        if (CheckCollisionPointRec(cursor, btnBoundsNewgame))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                btnStateNewgame = 2;

            }
            else btnStateNewgame = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                btnActionNewgame = true;
                SENDED_INFO.instruction = JOIN_LOBBY_INS;
                SENDED_INFO.name_room_created = "PDPDPDPDP";
            }
        }
        else btnStateNewgame = 0;

        if (CheckCollisionPointRec(cursor, btnBoundsSolo))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                btnStateSolo = 2;

            }
            else btnStateSolo = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                btnActionSolo = true;
                //INSTRUCTION ICI
            }
        }
        else btnStateSolo = 0;

        if (CheckCollisionPointRec(cursor, btnBoundsOption))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                btnStateSettings = 2;
            else btnStateSettings = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                btnActionSettings = true;
                //INSTRUCTION ICI
        }
        else btnStateSettings = 0;

        if (CheckCollisionPointRec(cursor, btnBoundsExit))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                btnStateExit = 2;
            else btnStateExit = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                btnActionExit = true;
                //INSTRUCTION ICI
        }
        else btnStateExit = 0;

        sourceRecNewgame.y = btnStateNewgame*frameHeightNewgame;

        sourceRecOption.y = btnStateSettings*frameHeightOption;

        sourceRecExit.y = btnStateExit*frameHeightExit;

        sourceRecSolo.y = btnActionSolo*frameHeightSolo;

        BeginDrawing();

        DrawTexture(Background, 0, 0, WHITE);

        DrawTextureRec(Create_room, sourceRecNewgame, (Vector2){ btnBoundsNewgame.x, btnBoundsNewgame.y }, WHITE); // Draw button frame

        DrawTextureRec(options, sourceRecOption, (Vector2){ btnBoundsOption.x, btnBoundsOption.y }, WHITE);

        DrawTextureRec(exit, sourceRecExit, (Vector2){ btnBoundsExit.x, btnBoundsExit.y }, WHITE);

        DrawTextureRec(Solo, sourceRecSolo, (Vector2){ btnBoundsSolo.x, btnBoundsSolo.y }, WHITE);

        EndDrawing();
}

void Menu::Menu_page()
{
    //std::cout << already_checked << std::endl;
    if (already_checked == 0) {
        Background = LoadTexture("assets/sprites/Background.png");
        exit = LoadTexture("assets/sprites/Exit.png");
        options = LoadTexture("assets/sprites/Settings.png");
        Create_room = LoadTexture ("assets/sprites/Newgame.png");
        Solo = LoadTexture("assets/sprites/Solo.png");
        cursor = { 0.0f, 0.0f };

        frameHeightNewgame = (float)Create_room.height/3;
        sourceRecNewgame = { 0, 0, (float)Create_room.width, frameHeightNewgame };
        btnBoundsNewgame = { 950 - Create_room.width/2.0f, 200 - Create_room.height/3/2.0f, (float)Create_room.width, frameHeightNewgame };

        frameHeightSolo = (float)Solo.height/3;
        sourceRecSolo = { 0, 0, (float)Solo.width, frameHeightSolo };
        btnBoundsSolo = { 950 - Solo.width/2.0f, 400 - Solo.height/3/2.0f, (float)Solo.width, frameHeightSolo };

        frameHeightOption = (float)options.height/3;
        sourceRecOption = { 0, 0, (float)options.width, frameHeightOption };
        btnBoundsOption = { 950 - options.width/2.0f, 600 - options.height/3/2.0f, (float)options.width, frameHeightOption };

        frameHeightExit = (float)exit.height/3;
        sourceRecExit = { 0, 0, (float)exit.width, frameHeightExit };
        btnBoundsExit = { 950 - exit.width/2.0f, 800 - exit.height/3/2.0f, (float)exit.width, frameHeightExit };

        btnStateNewgame = 0;
        btnActionNewgame = false;

        btnStateSettings = 0;
        btnActionSettings = false;

        btnStateExit = 0;
        btnActionExit = false;

        btnStateSolo = 0;
        btnActionSolo = false;

        Display();
    }
    else {
        Display();
    }
    already_checked++;
    //std::cout << already_checked << std::endl;
}

Menu::~Menu()
{
    UnloadTexture(Background);
    UnloadTexture(exit);
    UnloadTexture(Create_room);
    UnloadTexture(options);
    UnloadTexture(Solo);
}