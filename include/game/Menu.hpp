/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier-test-ecs
** File description:
** Menu
*/

/**
 * @file Menu.hpp
 * @brief Menu class
 * @version 0.1
 * @date 2022-10-17
 *
 */

#ifndef Menu_
#define Menu_

#include "game/Macro.hpp"
#include <boost/asio.hpp>
#include "server/serialize.hpp"
#include "raylib.h"

using boost::asio::ip::udp;

class Menu
{
private:
    public:
        Texture2D Background;
        Texture2D exit;
        Texture2D options;
        Texture2D Create_room;
        Texture2D join_room;
        Texture2D Solo;
        int join_looby;
        int already_checked;
        //class template pour assign une value;
        float frameHeightNewgame;
        Rectangle sourceRecNewgame;
        Rectangle btnBoundsNewgame;
        float frameHeightSolo;
        Rectangle sourceRecSolo;
        Rectangle btnBoundsSolo;
        float frameHeightOption;
        Rectangle sourceRecOption;
        Rectangle btnBoundsOption;
        float frameHeightExit;
        Rectangle sourceRecExit;
        Rectangle btnBoundsExit;
        Vector2 cursor;
        int btnStateNewgame;
        bool btnActionNewgame;
        int btnStateSettings;
        bool btnActionSettings;
        int btnStateExit;
        bool btnActionExit;
        int btnStateSolo;
        bool btnActionSolo;
        INSTRUCTION_GENERIC SENDED_INFO;
        void Menu_page();
        Menu();
        void Display();
        ~Menu();
};

#endif