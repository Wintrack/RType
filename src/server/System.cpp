/*
** EPITECH PROJECT, 2022
** TEK3
** File description:
** System
*/

/**
 * @file System.cpp
 * @brief System function
 * @version 0.1
 * @date 2022-10-17
 *
 */


#include "../../include/server/System.hpp"
#include <unistd.h>
#include <fstream>
#include "c_Entity.hpp"
using namespace Systems;

MovementSystem::MovementSystem()
{
    lock = 0;
    alive = 0;
}

MovementSystem::~MovementSystem()
{
}

std::vector<iEntity *> MovementSystem::World_Movement_handler(std::vector<iEntity *> DATABASE, std::vector<s_Entity> ram, int *id_generator)
{
    std::cout << "_____________________MovementSystem________________________" << std::endl;
    int i = 0;
    std::vector<iEntity *> tampon;
    std::vector<iEntity *> tmp;
    int all_x = 0;
    std::cout << "I = " << i << std::endl;
    std::cout << "type = " << DATABASE.at(i)->getStruc()->type << std::endl;
    while (i != DATABASE.size())
    {
        tampon = DATABASE.at(i)->Movement_handler(DATABASE);
        for (int j = 0; j < tampon.size(); j++) {
            if (tampon.at(j) != static_cast<iEntity *>(NULL)) {
                std::cout << "BULLET SHOT MOVEMENT HANDLER" << std::endl;
                tampon.at(j)->getStruc()->id = *id_generator;
                std::cout << *id_generator << std::endl;
                *id_generator += 1;
                std::cout << *id_generator << std::endl;
                tmp.push_back(tampon.at(j));
            }
        }
        i++;
    }
    for (int i = 0; i < tmp.size(); i++) {
        if (sizeof(tmp.at(i)) > 0) {
            DATABASE.push_back(tmp.at(i));
        }
    }
    return (DATABASE);
}

// Gravity

CollisionSystem::CollisionSystem()
{
}

CollisionSystem::~CollisionSystem()
{
}

std::vector<std::vector<int>> CollisionSystem::Collision_handler(s_Entity target, std::vector<s_Entity> *RAMMED_DATABASE)
{
    std::cout << "______________COLLISION HANDLER___________________" << std::endl;
    std::vector<std::vector<std::vector<s_Entity>>> Hit_Final;
    std::vector<std::vector<s_Entity>> Hit_result;
    std::vector<s_Entity> hitted;
    std::vector<s_Entity> hitted_by;
    std::vector<std::vector<int>> ids;
    std::vector<int> tab;
    if (target.pos_x >= 1830)
        target.pos_x = 1830;
    if (target.pos_x <= 0)
        target.pos_x = 0;
    if (target.pos_y >= 990)
        target.pos_y = 990;
    if (target.pos_y <= 0)
        target.pos_y = 0;
    int index = 0;
    if (target.i_frame <= 0) {
        while (index != RAMMED_DATABASE->size())
        {
            if (RAMMED_DATABASE->at(index).id != target.id)
            {
                if (target.pos_x + 90 >= RAMMED_DATABASE->at(index).pos_x && target.pos_x <= RAMMED_DATABASE->at(index).pos_x + 32
                && target.pos_y + 90 >= RAMMED_DATABASE->at(index).pos_y && target.pos_y <= RAMMED_DATABASE->at(index).pos_y + 10)
                {
                    if (target.type == 1) {
                        std::cout << "COLLISION MAUDITE" << std::endl;
                    }
                    std::cout << "GET HITTED" << std::endl;
                    hitted_by.push_back(RAMMED_DATABASE->at(index));
                    hitted.push_back(target);
                    Hit_result.push_back(hitted);
                    Hit_result.push_back(hitted_by);
                    tab.push_back(target.id);
                    tab.push_back(RAMMED_DATABASE->at(index).id);
                    ids.push_back(tab);
                }
                if (Hit_result.size() > 0)
                    Hit_Final.push_back(Hit_result);
                hitted_by.clear();
                hitted.clear();
                Hit_result.clear();
                tab.clear();
            }
            index++;
        }
    }
    std::cout << "HIT FINAL SIZE = " << Hit_Final.size() << std::endl;
    std::cout << "____________________FIN COLLISION HANDLER_________________" << std::endl;
    return (ids);
}

std::vector<std::vector<std::vector<s_Entity>>> CollisionSystem::World_Collision_handler(std::vector<iEntity *> RAMMED_DATABASE)
{
    std::cout << "______________COLLISION HANDLER___________________" << std::endl;
    std::vector<std::vector<std::vector<s_Entity>>> Hit_Final;
    std::vector<std::vector<s_Entity>> Hit_result;
    std::vector<s_Entity> hitted;
    std::vector<s_Entity> hitted_by;
    int index = 0;
    std::vector<iEntity *> bullets;
    std::vector<iEntity *> others;
    for (int i = 0; i < RAMMED_DATABASE.size(); i++)
    {
        if (RAMMED_DATABASE.at(i)->getStruc()->type == 4)
        {
            bullets.push_back(RAMMED_DATABASE.at(i));
        }
        if (RAMMED_DATABASE.at(i)->getStruc()->type == 6 && RAMMED_DATABASE.at(i)->getStruc()->underType == 1) {
            for (int j = 0; j < static_cast<Boss *>(RAMMED_DATABASE.at(i))->PARTS.size(); j++) {
                others.push_back(new Dummy(static_cast<Boss *>(RAMMED_DATABASE.at(i))->PARTS.at(j)));
            }
            others.push_back(RAMMED_DATABASE.at(i));
        }
        else
            others.push_back(RAMMED_DATABASE.at(i));
    }
    while (index != bullets.size())
    {
        for (int j = 0; j < others.size(); j++)
        {
            if (bullets.at(index)->getStruc()->pos_x >= others.at(j)->getStruc()->pos_x && bullets.at(index)->getStruc()->pos_x <= others.at(j)->getStruc()->pos_x + others.at(j)->width && bullets.at(index)->getStruc()->pos_y >= others.at(j)->getStruc()->pos_y && bullets.at(index)->getStruc()->pos_y <= others.at(j)->getStruc()->pos_y + others.at(j)->height && others.at(j)->getStruc()->type != 1) {
                if ((others.at(j)->getStruc()->type == 2) && static_cast<Bullet *>(bullets.at(index))->isAllied == true) {
                    std::cout << "GET HITTED" << std::endl;
                    hitted_by.push_back(*(others.at(j)->getStruc()));
                    hitted.push_back(*(bullets.at(index)->getStruc()));
                    Hit_result.push_back(hitted);
                    Hit_result.push_back(hitted_by);
                }
                else if ((others.at(j)->getStruc()->type != 2 && others.at(j)->getStruc()->type != 6) && static_cast<Bullet *>(bullets.at(index))->isAllied == false) {
                    std::cout << "GET HITTED" << std::endl;
                    hitted_by.push_back(*(others.at(j)->getStruc()));
                    hitted.push_back(*(bullets.at(index)->getStruc()));
                    Hit_result.push_back(hitted);
                    Hit_result.push_back(hitted_by);
                }
                else if ((others.at(j)->getStruc()->type == 6) && static_cast<Bullet *>(bullets.at(index))->isAllied == true) {
                    std::cout << "GET HITTED BOSS" << std::endl;
                    hitted_by.push_back(*(others.at(j)->getStruc()));
                    hitted.push_back(*(bullets.at(index)->getStruc()));
                    Hit_result.push_back(hitted);
                    Hit_result.push_back(hitted_by);
                }
            }
/*             if (static_cast<BouncingBullet *>(bullets.at(index))->rebond >= 3) {
                hitted.push_back(*(bullets.at(index)))
            } */
            if (Hit_result.size() > 0)
                Hit_Final.push_back(Hit_result);
            hitted_by.clear();
            hitted.clear();
            Hit_result.clear();
        }
        index++;
    }
    std::cout << "HIT FINAL SIZE = " << Hit_Final.size() << std::endl;
    std::cout << "____________________FIN COLLISION HANDLER_________________" << std::endl;
    return (Hit_Final);
}

HealthSystem::HealthSystem()
{
}

HealthSystem::~HealthSystem()
{
}

std::vector<s_Entity> HealthSystem::Health_handler(std::vector<std::vector<std::vector<s_Entity>>> Hit_result)
{
/*     std::vector<s_Entity> entities_to_update;
        std::cout << "_________________PRINT_COLLIS HEALTH HANDLER____________________" << std::endl;
    for (int i = 0; i < Hit_result.size(); i++) {
        for (int j = 0; j < Hit_result.at(i).size(); j++) {
            for (int k = 0; k < Hit_result.at(i).at(j).size(); k++) {
                std::cout << "Hit_res.at(" << i << ").at(" << j <<").at(" << k << ").id = " << Hit_result.at(i).at(j).at(k).id << "& type = " << Hit_result.at(i).at(j).at(k).type << std::endl;
            }
        }
    }
    std::cout << "___________AVANT_IF__________________" << std::endl;

    if (Hit_result.size() != 0)
    {
        std::cout << Hit_result.at(0).at(0).at(0).type << std::endl;
        std::cout << Hit_result.at(0).at(1).at(0).type << std::endl;
        std::cout << "________________IF HIT_RESULT_SIZE____________________" << std::endl;
        int i = 0;
        int x = 0;
        for (int j = 0; j < Hit_result.size(); j++)
        {
            std::cout << "________________________HEALTH LOOP____________________" << std::endl;
            std::cout << "Hit_result.size() = " << Hit_result.size() << std::endl;
            std::cout << "I = " << i << std::endl;
            if (Hit_result.at(j).at(i).size() != 0)
            {
                if (Hit_result.at(j).at(0).at(0).type == 2 && Hit_result.at(j).at(1).at(0).type == 2)
                {
                    // continue;
                }
                if (Hit_result.at(j).at(0).at(0).type == 1 && Hit_result.at(j).at(1).at(0).type == 5)
                {
                    Hit_result.at(j).at(0).at(0).pos_x = (Hit_result.at(j).at(1).at(0).pos_x - 110);
                    std::cout << "IF 1" << std::endl;
                    entities_to_update.push_back(Hit_result.at(j).at(0).at(0));
                }
                if (Hit_result.at(j).at(0).at(0).type == 1 && Hit_result.at(j).at(1).at(0).type == 2 && Hit_result.at(j).at(0).at(0).i_frame <= 0)
                {
                    Hit_result.at(j).at(0).at(0).health -= 15 * Hit_result.at(j).at(1).at(0).damage;
                    std::cout << "IF 2" << std::endl;
                    std::cout << "I_FRAME = " << Hit_result.at(j).at(0).at(0).i_frame << std::endl;
                    entities_to_update.push_back(Hit_result.at(j).at(0).at(0));
                }
                if (Hit_result.at(j).at(0).at(0).type == 4 && Hit_result.at(j).at(1).at(0).type == 2)
                {
                    std::cout << "IF 3" << std::endl;
                    Hit_result.at(j).at(0).at(0).health -= 50 * Hit_result.at(j).at(1).at(0).damage;
                    Hit_result.at(j).at(1).at(0).health -= 100 * Hit_result.at(j).at(0).at(0).damage;
                    entities_to_update.push_back(Hit_result.at(j).at(0).at(0));
                    entities_to_update.push_back(Hit_result.at(j).at(1).at(0));
                }
                if (Hit_result.at(j).at(0).at(0).type == 4 && Hit_result.at(j).at(1).at(0).type == 5)
                {
                    std::cout << "IF 4" << std::endl;
                    Hit_result.at(j).at(0).at(0).health -= 50 * Hit_result.at(j).at(1).at(0).damage;
                    entities_to_update.push_back(Hit_result.at(j).at(0).at(0));
                }
                if (Hit_result.at(j).at(0).at(0).type == 4 && Hit_result.at(j).at(1).at(0).type == 1 && Hit_result.at(j).at(0).at(0).i_frame <= 0)
                {
                    std::cout << "IF 4" << std::endl;
                    Hit_result.at(j).at(0).at(0).health -= 50 * Hit_result.at(j).at(1).at(0).damage;
                    std::cout << "I_FRAME = " << Hit_result.at(j).at(0).at(0).i_frame << std::endl;
                    entities_to_update.push_back(Hit_result.at(j).at(0).at(0));
                }
                i++;
            }
        }
    }
    for (int d = 0; d < entities_to_update.size(); d++)
    {
        if (entities_to_update.at(d).health >= 0)
        {
            std::cout << "__________IF FOR ENTITIES _______________D = " << d << std::endl;
            // entities_to_update.at(d).On_screen = false;
        }
    }
    std::cout << "________________FIN HEALTH SYSTEM ________________________________" << std::endl;
    return (entities_to_update); */
}

std::vector<s_Entity> HealthSystem::World_Health_handler(std::vector<std::vector<std::vector<s_Entity>>> Hit_result)
{
    std::cout << "_________________PRINT_COLLIS WRLD HEALTH HANDLER____________________" << std::endl;
    for (int i = 0; i < Hit_result.size(); i++) {
        for (int j = 0; j < Hit_result.at(i).size(); j++) {
            for (int k = 0; k < Hit_result.at(i).at(j).size(); k++) {
                std::cout << "Hit_res.at(" << i << ").at(" << j <<").at(" << k << ").id = " << Hit_result.at(i).at(j).at(k).id << "& type = " << Hit_result.at(i).at(j).at(k).type << std::endl;
            }
        }
    }
    //usleep(15000);
    std::vector<s_Entity> entities_to_update;
    std::cout << "___________AVANT_IF__________________" << std::endl;

    if (Hit_result.size() != 0)
    {
        std::cout << Hit_result.at(0).at(0).at(0).type << std::endl;
        std::cout << Hit_result.at(0).at(1).at(0).type << std::endl;
        std::cout << "________________IF HIT_RESULT_SIZE____________________" << std::endl;
        int i = 0;
        int x = 0;
        for (int j = 0; j < Hit_result.size(); j++)
        {
            std::cout << "________________________HEALTH LOOP____________________" << std::endl;
            std::cout << "Hit_result.size() = " << Hit_result.size() << std::endl;
            for (int i = 0; i < (Hit_result.at(j).at(i).size()); i++)
            {
                std::cout << "________________IF HIT RESULT_____________" << std::endl;
                if (Hit_result.at(j).at(i).at(0).type == 2 && Hit_result.at(j).at(i + 1).at(0).type == 2)
                {
                    // continue;
                }
                if (Hit_result.at(j).at(i).at(0).type == 4 && Hit_result.at(j).at(i + 1).at(0).type == 2)
                {
                    std::cout << "IF 3" << std::endl;
                    Hit_result.at(j).at(i).at(0).health -= 50 * Hit_result.at(j).at(i + 1).at(0).damage;
                    Hit_result.at(j).at(i + 1).at(0).health -= 100 * Hit_result.at(j).at(i).at(0).damage;
                    entities_to_update.push_back(Hit_result.at(j).at(i).at(0));
                    entities_to_update.push_back(Hit_result.at(j).at(i + 1).at(0));
                }
                if (Hit_result.at(j).at(i).at(0).type == 4 && Hit_result.at(j).at(i + 1).at(0).type == 5)
                {
                    std::cout << "IF 4" << std::endl;
                    Hit_result.at(j).at(i).at(0).health -= 50 * Hit_result.at(j).at(i + 1).at(0).damage;
                    entities_to_update.push_back(Hit_result.at(j).at(i).at(0));
                }
                if (Hit_result.at(j).at(i).at(0).type == 4 && Hit_result.at(j).at(i + 1).at(0).type == 3)
                {
                    std::cout << "IF 5" << std::endl;
                    Hit_result.at(j).at(i).at(0).health -= 50 * Hit_result.at(j).at(i + 1).at(0).damage;
                    Hit_result.at(j).at(i + 1).at(0).health -= 50 * Hit_result.at(j).at(i).at(0).damage;
                    entities_to_update.push_back(Hit_result.at(j).at(i).at(0));
                    entities_to_update.push_back(Hit_result.at(j).at(i + 1).at(0));
                }
                if (Hit_result.at(j).at(i).at(0).type == 4 && Hit_result.at(j).at(i + 1).at(0).type == 1)
                {
                    std::cout << "IF 6" << std::endl;
                    Hit_result.at(j).at(i).at(0).health -= 50 * Hit_result.at(j).at(i + 1).at(0).damage;
                    Hit_result.at(j).at(i + 1).at(0).health -= 15 * Hit_result.at(j).at(i).at(0).damage;
                    entities_to_update.push_back(Hit_result.at(j).at(i).at(0));
                }
                if (Hit_result.at(j).at(i).at(0).type == 4 && Hit_result.at(j).at(i + 1).at(0).type == 6)
                {
                    std::cout << "IF 7" << std::endl;
                    Hit_result.at(j).at(i).at(0).health -= 50 * Hit_result.at(j).at(i + 1).at(0).damage;
                    Hit_result.at(j).at(i + 1).at(0).health -= 15 * Hit_result.at(j).at(i).at(0).damage;
                    entities_to_update.push_back(Hit_result.at(j).at(i).at(0));
                    entities_to_update.push_back(Hit_result.at(j).at(i + 1).at(0));
                }
            }
        }
    }
    for (int d = 0; d < entities_to_update.size(); d++)
    {
        if (entities_to_update.at(d).health >= 0)
        {
            std::cout << "__________IF FOR ENTITIES _______________D = " << d << std::endl;
            // entities_to_update.at(d).On_screen = false;
        }
    }
    std::cout << "________________FIN HEALTH SYSTEM ________________________________" << std::endl;
    return (entities_to_update);
}

LivingSystem::LivingSystem()
{
}

LivingSystem::~LivingSystem()
{
}

std::vector<iEntity *> LivingSystem::Living_handler(std::vector<iEntity *> db, int *id_generator)
{
    std::cout << "___________________LIVING_________________" << std::endl;
    for (int i = 0; i < db.size(); i++) {
        if (db.at(i)->getStruc()->type == 2 && db.at(i)->getStruc()->underType == 3) {
            for (int j = 0; j < static_cast<ComposedEnemy *>(db.at(i))->PARTS.size(); j++) {
                if (static_cast<ComposedEnemy *>(db.at(i))->PARTS.at(j).health <= 0) {
                    static_cast<ComposedEnemy *>(db.at(i))->PARTS.erase(static_cast<ComposedEnemy *>(db.at(i))->PARTS.begin() + j);
                    j--;
                }
            }
        }
        if (db.at(i)->getStruc()->health <= 0) {
            if (db.at(i)->getStruc()->type == 2 || db.at(i)->getStruc()->type == 4 || db.at(i)->getStruc()->type == 3 || db.at(i)->getStruc()->type == 6) {
                if (db.at(i)->getStruc()->type == 2) {
                    int rand = std::rand() % 100;
                    if (rand <= 34) {
                        std::cout << "IF RAND" << std::endl;
                        int underRand = std::rand() % 100;
                        int bonus_under = 3;
                        if (underRand <= 1) {
                            bonus_under = 5;
                        }
                        if (underRand >= 2 && underRand <= 13) {
                            bonus_under = 2;
                        }
                        if (underRand >= 14 && underRand <= 54) {
                            bonus_under = 3;
                        }
                        else if (underRand >= 55 && underRand <= 75) {
                            bonus_under = 4;
                        }
                        else if (underRand >= 76 && underRand <= 100) {
                            bonus_under = 1;
                        }
                        s_Entity tmp = {3, bonus_under, *id_generator, 50, db.at(i)->getStruc()->pos_y, db.at(i)->getStruc()->pos_x, 0, 0, 0, false};
                        Bonus *entity = new Bonus(tmp);
                        db.push_back(entity);
                        *id_generator++;        
                    }
                }
                db.erase(db.begin() + i);
                std::cout << "db.erase(" << i << ") = " << std::endl;
            }
        }
    }
    std::cout << "_________________FIN LIVING_______________" << std::endl;
    return (db);
}

FrameSystem::FrameSystem()
{
    count = 30;
    value = 1;
}

FrameSystem::~FrameSystem()
{
}

std::vector<iEntity *> FrameSystem::World_Frame_handler(std::vector<iEntity *> DATABASE)
{
    std::cout << "__________________FRAME WORLD HANDLER__________________" << std::endl;
    int i = 0;
    if (count == 0) {
        std::cout << "DB.size() = " << DATABASE.size() << std::endl;
        while (i != DATABASE.size()) {
            DATABASE.at(i)->Frame_handler();
            i++;
        }
        count = 30;
    }
    else count--;
    for (int j = 0; j < DATABASE.size(); j++) {
        if (DATABASE.at(j)->getStruc()->i_frame != 0 && DATABASE.at(j)->struc.type == 1) {
            DATABASE.at(j)->getStruc()->i_frame--;
            std::cout << "i_frame = " << DATABASE.at(j)->getStruc()->i_frame << std::endl;
        }
    }
    std::cout << "COUNT = " << count << std::endl;
    std::cout << "______________FIN FRAME WORLD HANDLER____________" << std::endl;
    return (DATABASE);
}

RAM_MEMORY_System::RAM_MEMORY_System()
{
}

RAM_MEMORY_System::~RAM_MEMORY_System()
{
}

std::vector<s_Entity> RAM_MEMORY_System::RAM_handler(std::vector<iEntity *> DATABASE)
{
    int x = 0;
    std::vector<s_Entity> RAM_MEMORY;
    // faudra ajouter la valeur du sprite + 90 pour éviter que ça dépop de l'écran en touchant le bout
    while (x != DATABASE.size())
    {
        if (DATABASE.at(x)->getStruc()->pos_x >= 0 && DATABASE.at(x)->getStruc()->pos_x < 1985 && DATABASE.at(x)->getStruc()->pos_y >= 0 && DATABASE.at(x)->getStruc()->pos_y < 1085)
        {
            RAM_MEMORY.push_back(*DATABASE.at(x)->getStruc());
            if (DATABASE.at(x)->getStruc()->type == 2 && DATABASE.at(x)->getStruc()->underType == 3) {
                for (int i = 0; i < static_cast<ComposedEnemy *>(DATABASE.at(x))->PARTS.size(); i++) {
                    RAM_MEMORY.push_back(static_cast<ComposedEnemy *>(DATABASE.at(x))->PARTS.at(i));
                }
            }
            if (DATABASE.at(x)->getStruc()->type == 6 && DATABASE.at(x)->getStruc()->underType == 1) {
                for (int i = 0; i < static_cast<Boss *>(DATABASE.at(x))->PARTS.size(); i++) {
                    RAM_MEMORY.push_back(static_cast<Boss *>(DATABASE.at(x))->PARTS.at(i));
                }
            }
            if (DATABASE.at(x)->getStruc()->type == 6 && DATABASE.at(x)->getStruc()->underType == 5) {
                for (int i = 0; i < static_cast<BigSnake *>(DATABASE.at(x))->PARTS.size(); i++) {
                    RAM_MEMORY.push_back(static_cast<BigSnake *>(DATABASE.at(x))->PARTS.at(i));
                }
            }
        }
        x++;
    }
    return (RAM_MEMORY);
}

RenderingSystem::RenderingSystem() : screenWidth(1920), screenHeight(1080), isHitted(0), starship(LoadTexture("assets/sprites/starship.png")), ennemy(LoadTexture("assets/sprites/ennemy.png")), background(LoadTexture("assets/sprites/background_level.png")), bullet(new fire("assets/sprites/bulletv1.png", {starshipPosition.x, starshipPosition.y}, true))
{

    // InitWindow(screenWidth, screenHeight, "background of the game");
    starshipPosition = {90, 150};
    Vector2 offset = {0, 0};
    healthset = 0;
    SetTargetFPS(60);
}

std::string Find_asset(c_Entity displayed_entity)
{
    std::string text_path;
    std::string my_entity;
    my_entity += std::to_string(displayed_entity.type);
    my_entity += ':';
    my_entity += std::to_string(displayed_entity.underType);
    std::cout << "MYENTITY " << my_entity << std::endl;
    std::ifstream file("config.txt");
    std::vector<std::string> config;
    std::string getlining;
    if (file.is_open()) {
        while (std::getline(file, getlining)) {
            config.push_back(getlining + '\n');
        }
        for (int i = 0; i < config.size(); i++) {
            //std::cout << "config.at(" << i << ") = " << config.at(i).substr(0, 3) << std::endl;
            if (config.at(i).substr(0, 3) == my_entity) {
                size_t pos1 = config.at(i + 9).find('"');
                size_t pos2 = config.at(i + 9).find('"', pos1 + 1);
                std::cout << "pos1 = " << pos1 << " && pos2 = " << pos2 << std::endl;
                text_path = config.at(i + 9).substr((pos1 + 1), (pos2 - 1));
                text_path.erase(text_path.end() - 1);
                text_path.erase(text_path.end() - 1);
                std::cout << "TEXT_PATH= " << text_path << std::endl;
                return (text_path);
            }
        }
    }
}

int Find_max_frame(c_Entity displayed_entity)
{
    std::string text_path;
    std::string my_entity;
    my_entity += std::to_string(displayed_entity.type);
    my_entity += ':';
    my_entity += std::to_string(displayed_entity.underType);
    std::cout << "MYENTITY " << my_entity << std::endl;
    std::ifstream file("config.txt");
    std::vector<std::string> config;
    std::string getlining;
    if (file.is_open()) {
        while (std::getline(file, getlining)) {
            config.push_back(getlining + '\n');
        }
        for (int i = 0; i < config.size(); i++) {
            //std::cout << "config.at(" << i << ") = " << config.at(i).substr(0, 3) << std::endl;
            if (config.at(i).substr(0, 3) == my_entity) {
                size_t pos1 = config.at(i + 6).find('=');
                size_t pos2 = config.at(i + 6).find('\n', pos1 + 1);
                std::cout << "pos1 = " << pos1 << " && pos2 = " << pos2 << std::endl;
                text_path = config.at(i + 6).substr((pos1 + 1), (pos2 - 1));
/*                 text_path.erase(text_path.end() - 1);
                text_path.erase(text_path.end() - 1); */
                std::cout << "MAX_FRAME= " << text_path << std::endl;
                return (atoi(text_path.c_str()));
            }
        }
    }
}

RenderingSystem::~RenderingSystem()
{
    UnloadTexture(starship);
    UnloadTexture(background);
    UnloadTexture(ennemy);
    // CloseWindow();
}

INSTRUCTION_GENERIC RenderingSystem::Rendering_handler(std::vector<s_Entity> new_displayed, int id)
{
/*     InitAudioDevice();
    Sound Sound1 = LoadSound("assets/audio/laser.wav"); */
    std::cout << "__________________________ CLIENT RENDER HERE __________________________" << std::endl;
    usleep(1500);
    std::vector<c_Entity> displayed;
    for (int i = 0; i < new_displayed.size(); i++) {
        c_Entity tmp;
        tmp.damage = new_displayed.at(i).damage;
        tmp.frame = new_displayed.at(i).frame;
        tmp.hasPLayed = new_displayed.at(i).hasPLayed;
        tmp.health = new_displayed.at(i).health;
        tmp.i_frame = new_displayed.at(i).i_frame;
        tmp.id = new_displayed.at(i).id;
        tmp.pos_x = new_displayed.at(i).pos_x;
        tmp.pos_y = new_displayed.at(i).pos_y;
        tmp.type = new_displayed.at(i).type;
        tmp.underType = new_displayed.at(i).underType;
        displayed.push_back(tmp);
    }
    SENDED_INFO.instruction = JOINED_GAME;
    std::cout << "displayed.size() = " << displayed.size() << std::endl;
    for (int i = 0; i < displayed.size(); i++)
    {
        std::string text_path = Find_asset(displayed.at(i));
        displayed.at(i).sprite = LoadTexture(text_path.c_str());
        std::cout << "I = " << i << " ID = " << displayed.at(i).id << " type = " << displayed.at(i).type << " health = " << displayed.at(i).health << " x = " << displayed.at(i).pos_x << " y = " << displayed.at(i).pos_y << " damage = " << displayed.at(i).damage << std::endl;
    }

    offset.x += GetFrameTime() * 50;

    BeginDrawing();

    ClearBackground(WHITE);
    DrawTexturePro(background, (Rectangle){offset.x, offset.y, GetScreenWidth(), GetScreenHeight()}, (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()}, (Vector2){0, 0}, 0, WHITE);
    int frameDelay = 0;
    int x = 0;
    while (x != displayed.size())
    {
        /* if (displayed.at(x).hasPLayed == false) {
            InitWindow(1, 1, "fx window");
            InitAudioDevice();
            Sound Sound1 = LoadSound("assets/sprites/laser.wav");
            PlaySound(Sound1);
            if (!WindowShouldClose())
            {
                if (!IsSoundPlaying(Sound1)) {
                    displayed.at(x).hasPLayed = true;
                    UnloadSound(Sound1);
                    CloseAudioDevice();
                    CloseWindow();
                }
            }
        } */
        if (displayed.at(x).type == 6) {
            if (displayed.at(x).underType == 1)
                DrawText("Evilmaxxer", displayed.at(x).pos_x, displayed.at(x).pos_y - 80, 50, BLACK);
            if (displayed.at(x).underType == 3)
                DrawText("Sol", displayed.at(x).pos_x, displayed.at(x).pos_y - 80, 30, BLACK);
            if (displayed.at(x).underType == 4)
                DrawText("Luna", displayed.at(x).pos_x, displayed.at(x).pos_y - 80, 30, BLACK);
        }
        if (displayed.at(x).id == id) {
            frameDelay = displayed.at(x).health;
            frameDelay = frameDelay / 10;
            if (frameDelay < 0)
                frameDelay = 0;
            for (int i = 0; i < 10; i++)
            {
                if (i < frameDelay)
                    DrawRectangle(1670 + 19*i, 100, 20, 20, RED);
                DrawRectangleLines(1670 + 19*i, 100, 20, 20, BLACK);
            }
        }
        if (displayed.at(x).type != 4 && displayed.at(x).id != id && displayed.at(x).type != 3 && displayed.at(x).type != 5) {
            if (displayed.at(x).underType != 4) {
                frameDelay = displayed.at(x).health;
                frameDelay = frameDelay / 10;
                if (frameDelay < 0)
                    frameDelay = 0;
                for (int i = 0; i < 10; i++)
                {
                    if (i < frameDelay)
                        DrawRectangle(displayed.at(x).pos_x + 9*i, displayed.at(x).pos_y - 50, 10, 10, RED);
                    DrawRectangleLines(displayed.at(x).pos_x + 9*i, displayed.at(x).pos_y - 50, 10, 10, BLACK);
                }
            }
        }
/*         if (displayed.at(x).hasPLayed == false)
            PlaySound(Sound1); */
        Rectangle _Rect_sources = {displayed.at(x).frame * displayed.at(x).sprite.width / Find_max_frame(displayed.at(x)), displayed.at(x).sprite.height, (float)displayed.at(x).sprite.width / Find_max_frame(displayed.at(x)), (float)displayed.at(x).sprite.height};
        DrawTextureRec(displayed.at(x).sprite, _Rect_sources, (Vector2){ displayed.at(x).pos_x, displayed.at(x).pos_y }, WHITE);
        std::cout << "FRAME OF CLIENT:" << displayed.at(x).frame <<std::endl;
        x++;
    }

    SENDED_INFO.info_player.clear();
    if (healthset < 1) {
        if (IsKeyPressed(KEY_SPACE))
            {
                std::cout << "KEYSPACEEEEEEEEEEEEEEEE" << std::endl;
                SENDED_INFO.info_player.push_back(2);
                SENDED_INFO.info_player.push_back(starshipPosition.x);
                SENDED_INFO.info_player.push_back(starshipPosition.y);
                SENDED_INFO.info_player.push_back(id);
            }
    }

        if (IsKeyDown(KEY_RIGHT))
            starshipPosition.x += 10;
        if (IsKeyDown(KEY_LEFT))
            starshipPosition.x -= 10;
        if (IsKeyDown(KEY_UP))
            starshipPosition.y -= 10;
        if (IsKeyDown(KEY_DOWN))
            starshipPosition.y += 10;
        if (IsKeyDown(KEY_D))
            starshipPosition.x += 10;
        if (IsKeyDown(KEY_Q))
            starshipPosition.x -= 10;
        if (IsKeyDown(KEY_Z))
            starshipPosition.y -= 10;

        if (IsKeyDown(KEY_S))
            starshipPosition.y += 10;


        if (starshipPosition.x >= 1830)
            starshipPosition.x = 1830;
        if (starshipPosition.x <= 0)
            starshipPosition.x = 0;
        if (starshipPosition.y >= 990)
            starshipPosition.y = 990;
        if (starshipPosition.y <= 0)
            starshipPosition.y = 0;

        SENDED_INFO.info_player.push_back(1);
        SENDED_INFO.info_player.push_back(starshipPosition.x);
        SENDED_INFO.info_player.push_back(starshipPosition.y);
        SENDED_INFO.info_player.push_back(id);
    EndDrawing();
    for (int i = 0; i < displayed.size(); i++) {
        UnloadTexture(displayed.at(i).sprite);
    }
    return (SENDED_INFO);
}