/*
** EPITECH PROJECT, 2022
** TEK3
** File description:
** ClientInternalLogic
*/

/**
 * @file ClientInternalLogic.hpp
 * @brief System class
 * @version 0.1
 * @date 2022-10-17
 *
 */

#ifndef CLIENTINTERNALLOGIC_HPP_
#define CLIENTINTERNALLOGIC_HPP_
#include "System.hpp"
class ClientInternalLogic {
    public:
        ClientInternalLogic(std::vector<s_Entity> Original_RAM, int new_id);
        ~ClientInternalLogic();
        void Client_Display(int new_id);
        void Verify_Cache(std::vector<s_Entity> Original_RAM);
        INSTRUCTION_GENERIC getInfos();
    protected:
        int id;
        INSTRUCTION_GENERIC SENDED_INFOS;
        Systems::RenderingSystem RenderSys;
        //Systems::AudioSystem AudioSys;
        std::vector<s_Entity> DATABASE;
        std::vector<s_Entity> CACHE;
        std::vector<s_Entity> Display_on_screen;
    private:
};

#endif /* !CLIENTINTERNALLOGIC_HPP_ */