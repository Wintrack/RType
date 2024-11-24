/*
** EPITECH PROJECT, 2022
** TEK3
** File description:
** ServerInternalLogic
*/

#include <iostream>
#include <fstream>
#include "../game/Entity.hpp"
#include "System.hpp"

#ifndef SERVERINTERNALLOGIC_HPP_
#define SERVERINTERNALLOGIC_HPP_

class ServerInternalLogic {
    public:
        ServerInternalLogic(std::string level_path);
        ~ServerInternalLogic();
        void Add_new_player();
        void DATABASE_Update(std::vector<s_Entity> entities_for_update);
        void Receive_from_client(int type, int pos_x, int pos_y, int id);
        iEntity *Create_entity(std::string str, int pos_y, int pos_x);
        void Asynchronic_Calculation();
        int Verify_ID(int id);
        std::vector<s_Entity> getRam();
        std::vector<int> CLIENT_IDS;
        std::vector<iEntity *> DATABASE;
        int id_generator;
        std::vector<s_Entity> RAM_DATABASE; //ce qui va être envoyé vers le client
    protected:
    private:
        Systems::CollisionSystem Collision;
        Systems::FrameSystem Frame;
        Systems::HealthSystem Health;
        Systems::RAM_MEMORY_System RAM;
        //Rajouter les systèmes que l'on veut;
};

#endif /* !SERVERINTERNALLOGIC_HPP_ */
