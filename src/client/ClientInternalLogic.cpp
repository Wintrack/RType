/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier-test-ecs
** File description:
** ClientInternalLogic
*/

/**
 * @file ClientInternalLogic.cpp
 * @brief This file contain most of what th client will do that do not concern th user
 * @version 0.1
 * @date 2022-10-17
 *
 */

#include "ClientInternalLogic.hpp"

ClientInternalLogic::ClientInternalLogic(std::vector<s_Entity> Original_RAM, int id_new) : RenderSys()
{
    DATABASE = Original_RAM;
    CACHE = DATABASE;
    id = id_new;
}

ClientInternalLogic::~ClientInternalLogic()
{
}

void ClientInternalLogic::Client_Display(int id_new)
{
    id = id_new;
    SENDED_INFOS = RenderSys.Rendering_handler(Display_on_screen, id);
    //AudioSys
}

INSTRUCTION_GENERIC ClientInternalLogic::getInfos()
{
    return (SENDED_INFOS);
}

void ClientInternalLogic::Verify_Cache(std::vector<s_Entity> Original_RAM)
{
    std::cout << "_________________VERIFY CACHE____________________" << std::endl;
    /*DATABASE = Original_RAM;
    CACHE = DATABASE;*/
    int x = 0;
    int y = 0;
    int valid_presence;
    std::cout << "Original_RAM.size() = " << Original_RAM.size() << std::endl;
    for (int i = 0; i < Original_RAM.size(); i++) {
        std::cout << "I = " << i << " type = " << Original_RAM.at(i).type << " health = " << Original_RAM.at(i).health << " x = " << Original_RAM.at(i).pos_x << " y = " << Original_RAM.at(i).pos_y << " damage = " << Original_RAM.at(i).damage << std::endl;
    }
    Display_on_screen.clear();
    for (int i = 0; i < Original_RAM.size(); i++) {
        Display_on_screen.push_back(Original_RAM.at(i));
    }
    std::cout << "____________________________FIN VERIFY CACHE_______________________________________" << std::endl;
}