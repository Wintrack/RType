/*
** EPITECH PROJECT, 2022
** TEK3
** File description:
** ServerInternalLogic
*/

/**
 * @file ServerInternalLogic.cpp
 * @brief ServerInternalLogic function
 * @version 0.1
 * @date 2022-10-17
 *
 */

#include "../../include/server/ServerInternalLogic.hpp"
#include <unistd.h>


ServerInternalLogic::ServerInternalLogic(std::string level_path)
{
    std::ifstream myfile(level_path);
    std::string myline;
    std::vector<std::string> map_level;
    std::vector<iEntity *> DATABASE2;
    std::cout << "LEVELPATH CONSTRUCTOR SERVERINTERNAL LOGIC:" << level_path << std::endl;
    id_generator = 0;
    int x = 0;
    int pos_x = 0;
    int y = 0;
    int pos_y = 0;
    int count_line;
    if (myfile.is_open())
    {
        while ( std::getline(myfile,myline) )
        {
            map_level.push_back(myline + '\n');
        }
        myfile.close();
    }
    while (y != map_level.size()) {
        while (x != map_level.at(y).size()) {
            if (map_level.at(y).at(x) != '0' && map_level.at(y).at(x) != '\n') {
                    if (map_level.at(y).at(x+1) == ':') {
                        std::string str;
                        str += map_level.at(y).at(x);
                        str += map_level.at(y).at(x+1);
                        str += map_level.at(y).at(x+2);
                        str += "\n";
                        std::cout << "STR = " << str << std::endl;
                        iEntity *tmp = Create_entity(str, pos_y, pos_x);
                        std::cout << "ON A RECUP TMP" << std::endl;
                        std::cout << "TYPE OF TMP = " << tmp->getStruc()->type << std::endl;
                        std::cout << "underType OF TMP = " << tmp->getStruc()->underType << std::endl;
                        if (tmp->getStruc()->type == 1) {
                            CLIENT_IDS.push_back(tmp->getStruc()->id);
                        }
                        std::cout << "AVANT PUSHBACK TMP" << std::endl;
                        DATABASE2.push_back(tmp);
                    }
                    x = x + 2;
                    pos_x += 90;
                    id_generator++;
            }
            else {
                x++;
                pos_x += 90;
            }
        }
        y++;
        pos_y += 90;
        x = 0;
        pos_x = 0;
    }
    DATABASE = DATABASE2;
    RAM_DATABASE = RAM.RAM_handler(DATABASE);
    std::cout << "____________________________________ PRINT DB __________________________" << std::endl;
    for (int i = 0; i < DATABASE.size(); i++) {
        std::cout << DATABASE.at(i)->getStruc()->damage << " " << DATABASE.at(i)->getStruc()->frame << " " << DATABASE.at(i)->getStruc()->health << DATABASE.at(i)->getStruc()->id << " " << " " << DATABASE.at(i)->getStruc()->pos_x << " " << DATABASE.at(i)->getStruc()->pos_y << " " << DATABASE.at(i)->getStruc()->type << std::endl; 
    }
    std::cout << "____________________________________ PRINT RAM DB __________________________" << std::endl;
    for (int i = 0; i != RAM_DATABASE.size(); i++) {
        std::cout << RAM_DATABASE.at(i).damage << " " << RAM_DATABASE.at(i).frame << " " << RAM_DATABASE.at(i).health << RAM_DATABASE.at(i).id << " "  << RAM_DATABASE.at(i).pos_x << " " << RAM_DATABASE.at(i).pos_y << " " << RAM_DATABASE.at(i).type << std::endl; 
    }
    std::cout << "____________________________________ PRINT RAM DB __________________________" << std::endl;
}

iEntity *ServerInternalLogic::Create_entity(std::string str, int pos_y, int pos_x)
{
    std::ifstream file("config.txt");
    std::string getlining;
    int player_id;
    std::vector<std::string> config;
    s_Entity temp = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    iEntity *ret;
    int max_frame = 0;
    int width = 0;
    int height = 0;
    int nb_part = 0;
    if (file.is_open()) {
        while (std::getline(file, getlining)) {
            config.push_back(getlining + '\n');
        }
        for (int i = 0; i < config.size(); i++) {
            if (config.at(i) == str) {
                temp.type = atoi(config.at(i + 2).substr(9, std::string::npos).c_str());
                temp.underType = atoi(config.at(i + 3).substr(14, std::string::npos).c_str() );
                temp.health = atoi(config.at(i + 4).substr(11, std::string::npos).c_str());
                temp.damage = atoi(config.at(i + 5).substr(11, std::string::npos).c_str());
                temp.pos_x = pos_x;
                temp.pos_y = pos_y;
                temp.id = id_generator;
                temp.frame = 0;
                max_frame = atoi(config.at(i + 6).substr(15, std::string::npos).c_str());
                width = atoi(config.at(i + 7).substr(10, std::string::npos).c_str());
                height = atoi(config.at(i + 8).substr(11, std::string::npos).c_str());
            }
        }
        std::cout << "width = " << width << " && height = " << height << std::endl;
        if(temp.type == 1) {
            temp.id = -5;
            std::cout << "pute" << std::endl;
            ret = new Player(temp);
            ret->max_frame = max_frame;
            ret->width = width;
            ret->height = height;
            std::cout << temp.underType << std::endl;
            return (ret);
        }
        else if(temp.type == 2) {
            if (temp.underType == 1) {
                ret = new Enemy(temp);
                ret->max_frame = max_frame;
                ret->width = width;
                ret->height = height;
                return (ret);
            }
            if (temp.underType == 2) {
                ret = new ShootingEnemy(temp);
                ret->max_frame = max_frame;
                ret->width = width;
                ret->height = height;
                return (ret);
            }
            else if (temp.underType == 3) {
                std::vector<s_Entity> body;
                int size = (std::rand() % 10) + 1;
                if (size == 1) {
                    size++;
                }
                for(int i = 0; i <= size; i++) {
                    std::cout << "I in composed = " << i << std::endl;
                    s_Entity tmp;
                    if (i == 0) {
                        tmp = {2, 3, id_generator, temp.health, temp.pos_y, temp.pos_x, temp.frame, temp.damage, 0, 0};
                    }
                    else {
                        tmp = {2, 4, id_generator, temp.health, temp.pos_y, temp.pos_x, temp.frame, temp.damage, 0, 0};
                    }
                    id_generator++;
                    temp.pos_x += 90;
                    body.push_back(tmp);
                }
                std::cout << "AVANT RET NEW COMPOSED" << std::endl;
                for (int i = 0; i < body.size(); i++) {
                    std::cout << "BODY.at(" << i << ").underType = " << body.at(i).underType << std::endl;
                }
                ret = new ComposedEnemy(body);
                ret->max_frame = 1;
                ret->width = width;
                ret->height = height;
                return (ret);
            }
        }
        else if (temp.type == 3) {
            if (temp.underType == 1) {
                ret = new Bonus(temp);
                ret->max_frame = 4;
                ret->width = width;
                ret->height = height;
                return (ret);
            }
            if (temp.underType == 2) {
                ret = new Weapon(temp);
                ret->max_frame = 4;
                ret->width = width;
                ret->height = height;
                return (ret);
            }
            if (temp.underType == 3) {
                ret = new Bonus(temp);
                ret->max_frame = 4;
                ret->width = width;
                ret->height = height;
                return (ret);
            }
            if (temp.underType == 4) {
                std::cout << "RET = BOUNCING BONUS" << std::endl;
                ret = new Bonus(temp);
                ret->max_frame = 4;
                ret->width = width;
                ret->height = height;
                return (ret);
            }
            if (temp.underType == 5) {
                std::cout << "RET = REVIVE" << std::endl;
                ret = new Bonus(temp);
                ret->max_frame = 4;
                ret->width = width;
                ret->height = height;
                return (ret);
            }
        }
        else if(temp.type == 4) {
            ret = new Bullet(temp, false);
            ret->max_frame = max_frame;
            ret->width = width;
            ret->height = height;
            std::cout << temp.underType << std::endl;
            return (ret);
        }
        else if(temp.type == 5) {
            ret = new Bloc(temp);
            ret->max_frame = max_frame;
            ret->width = width;
            ret->height = height;
            std::cout << temp.underType << std::endl;
            return (ret);
        }
        else if(temp.type == 6) {
            if (temp.underType == 1) {
                std::vector<s_Entity> body;
                s_Entity tmp;
                std::cout << "temp.pos_y =" << temp.pos_y << std::endl;
                tmp = {6, 1, id_generator, temp.health, temp.pos_y, temp.pos_x, temp.frame, temp.damage, 0, 0};
                body.push_back(tmp);
                id_generator++;
                tmp = {6, 2, id_generator, temp.health - 600, temp.pos_y - 300, temp.pos_x - 50, temp.frame, temp.damage, 0, 0};
                body.push_back(tmp);
                id_generator++;
                tmp = {6, 2, id_generator, temp.health - 600, temp.pos_y + 300, temp.pos_x - 50, temp.frame, temp.damage, 0, 0};
                body.push_back(tmp);
                id_generator++;
                //temp.pos_x += 90;
                std::cout << "AVANT RET NEW COMPOSED" << std::endl;
                for (int i = 0; i < body.size(); i++) {
                    std::cout << "BODY.at(" << i << ").underType = " << body.at(i).underType << std::endl;
                }
                ret = new Boss(body);
                ret->max_frame = max_frame;
                ret->width = width;
                ret->height = height;
                return (ret);
            }
            if (temp.underType == 3) {
                ret = new Sol(temp);
                ret->max_frame = max_frame;
                ret->width = width;
                ret->height = height;
                return (ret);
            }
            if (temp.underType == 4) {
                ret = new Luna(temp);
                ret->max_frame = max_frame;
                ret->width = width;
                ret->height = height;
                return (ret);
            }
            if (temp.underType == 5) {
                std::vector<s_Entity> body;
                int size = 4;
                for(int i = 0; i <= size; i++) {
                    std::cout << "I in composed = " << i << std::endl;
                    s_Entity tmp;
                    if (i == 0) {
                        tmp = {6, 5, id_generator, temp.health, temp.pos_y, temp.pos_x, temp.frame, temp.damage, 0, 0};
                    }
                    else {
                        tmp = {6, 6, id_generator, temp.health, temp.pos_y, temp.pos_x, temp.frame, temp.damage, 0, 0};
                    }
                    id_generator++;
                    temp.pos_x += 180;
                    body.push_back(tmp);
                }
                std::cout << "AVANT RET NEW COMPOSED" << std::endl;
                for (int i = 0; i < body.size(); i++) {
                    std::cout << "BODY.at(" << i << ").underType = " << body.at(i).underType << std::endl;
                }
                ret = new BigSnake(body);
                ret->max_frame = 1;
                ret->width = 540;
                ret->height = 180;
                return (ret);
            }
        }
        file.close();
    }
}

ServerInternalLogic::~ServerInternalLogic()
{
    CLIENT_IDS.clear();
    DATABASE.clear();
    RAM_DATABASE.clear();
}

void ServerInternalLogic::Add_new_player()
{
    s_Entity entity;
    entity.type = 1;
    entity.underType = 1;
    entity.id = id_generator; // A MODIF
    id_generator++;
    CLIENT_IDS.push_back(entity.id);
    entity.health = 100;
    entity.pos_x = 15;
    entity.pos_y = 300;
    //mettre la hitbox
    entity.frame = 0;
    entity.damage = 1;
    entity.i_frame = 0;
    Player *tmp = new Player(entity);
    DATABASE.push_back(tmp);
    RAM_DATABASE = RAM.RAM_handler(DATABASE);
}

/*
if (DATABASE.at(i)->getStruc()->type == 6) {
    for (int i = 0; i != static_cast<Boss *>(DATABASE.at(i))->PARTS.size(); i++) {
        Dummy *dum = new Dummy(static_cast<Boss *>(DATABASE.at(i))->PARTS.at(i));
        tmp.push_back(dum);
    }
}
*/

void ServerInternalLogic::Asynchronic_Calculation()
{
    std::cout << "____________ASYNCRO CALC______________" << std::endl;
    for (int i = 0; i < RAM_DATABASE.size(); i++) {
        std::cout << "I = " << i << " type = " << RAM_DATABASE.at(i).type << " health = " << RAM_DATABASE.at(i).health << " x = " << RAM_DATABASE.at(i).pos_y << " y = " << RAM_DATABASE.at(i).pos_x << " damage = " << RAM_DATABASE.at(i).damage << std::endl;
    }
    Systems::MovementSystem Movement;
    Systems::LivingSystem Living;
    std::vector<std::vector<std::vector<s_Entity>>> Collis;
    std::vector<s_Entity> entities_to_update;
    for (int i = 0; i < DATABASE.size(); i++) {
        std::cout << "Id = " << DATABASE.at(i)->struc.id << "\t Health =" << DATABASE.at(i)->struc.health << "\tType = " << DATABASE.at(i)->struc.type << "\tunderType = " << DATABASE.at(i)->struc.underType << "\tposX = " << DATABASE.at(i)->struc.pos_x << " posY = " << DATABASE.at(i)->struc.pos_y << std::endl;
    }
    RAM_DATABASE = RAM.RAM_handler(DATABASE);
    DATABASE = Movement.World_Movement_handler(DATABASE, RAM_DATABASE, &id_generator);
    DATABASE = Frame.World_Frame_handler(DATABASE);
    RAM_DATABASE = RAM.RAM_handler(DATABASE);
    Collis = Collision.World_Collision_handler(DATABASE);
    std::cout << "__________________WORLD HEALTH HANDLER______________" << std::endl;
    entities_to_update = Health.World_Health_handler(Collis);
    std::cout << "__________________POST WORLD HEALTH HANDLER______________" << std::endl;
    DATABASE_Update(entities_to_update);
    DATABASE = Living.Living_handler(DATABASE, &id_generator);
    RAM_DATABASE = RAM.RAM_handler(DATABASE);
    std::cout << "______________________AFTER UPDATE_________________" << std::endl;
    for (int i = 0; i < RAM_DATABASE.size(); i++) {
        std::cout << "I = " << i << " type = " << RAM_DATABASE.at(i).type << " health = " << RAM_DATABASE.at(i).health << " x = " << RAM_DATABASE.at(i).pos_y << " y = " << RAM_DATABASE.at(i).pos_x << " damage = " << RAM_DATABASE.at(i).damage << std::endl;
    }
}

void ServerInternalLogic::DATABASE_Update(std::vector<s_Entity> entities_for_update)
{
    int x = 0;
    int g = 0;
    std::cout << "_________________DATABASEUPDATE_________________" << std::endl;
    for (int o = 0; o != entities_for_update.size(); o++)
    {
        std::cout << "ENTITIES TO UPDATE\n";
        std::cout << entities_for_update.at(o).type << std::endl;
        std::cout << entities_for_update.at(o).underType << std::endl;
        std::cout << std::endl;
    }
    while (x != entities_for_update.size()) {
        if (entities_for_update.at(x).type == 6 && entities_for_update.at(x).underType == 2) {
            std::cout << "IN 6:2" << std::endl;
            int index = 0;
            int ret_index = 0;
            for (int z = 0; z != DATABASE.size(); z++) {
                if (DATABASE.at(z)->getStruc()->type == 6 && DATABASE.at(z)->getStruc()->underType == 1) 
                    ret_index = z;
            }
            std::cout << "IN 6:2 2" << std::endl;
            for (int i = 0; i < static_cast<Boss *>(DATABASE.at(ret_index))->PARTS.size(); i++) {
                if (static_cast<Boss *>(DATABASE.at(ret_index))->PARTS.at(i).id == entities_for_update.at(x).id) {
                    static_cast<Boss *>(DATABASE.at(ret_index))->PARTS.at(i) = entities_for_update.at(x);
                }
            }
            std::cout << "IN 6:2 3" << std::endl;

            std::cout << "AFTER CAST CHELOU" << std::endl;
        }
        else {
            int index = this->Verify_ID(entities_for_update.at(x).id);
            DATABASE.at(index)->get_update(entities_for_update.at(x));
        }
        x++;
    }
    std::cout << "APRES PREMIER WHILE" << std::endl;
    int size = DATABASE.size();
    while (g != size) {
        if (DATABASE.at(g)->getStruc()->pos_x + 90 <= 0) {
            DATABASE.erase(DATABASE.begin()+g);
            size = DATABASE.size();
            g = 0;
        }
        else {
            g++;
        }
    }
    std::cout << "_______________FINDATABASEUPDATE________________" << std::endl;
}

void ServerInternalLogic::Receive_from_client(int type, int pos_x, int pos_y, int id)
{
    std::cout << "________________RECEIVE FROM CLIENT_____________________" << std::endl;
    std::vector<std::vector<std::vector<s_Entity>>> Hit_result;
    std::vector<s_Entity> Entities_to_update;
    std::vector<std::vector<int>> ids;
    std::cout << "type = " << type << " x = " << pos_x << " y = " << pos_y << " id = " << id << std::endl;

    int healthCheck = this->Verify_ID(id);
    if (type == 1) {
        std::cout << "TYPE 1" << std::endl;
        int index_for_target_entity = this->Verify_ID(id);
        std::cout << "index = " << index_for_target_entity << std::endl;
        DATABASE.at(index_for_target_entity)->getStruc()->pos_y = pos_y;
        DATABASE.at(index_for_target_entity)->getStruc()->pos_x = pos_x;
        std::cout << "ON A PASSE ID " << std::endl;
        ids = Collision.Collision_handler(*(DATABASE.at(index_for_target_entity)->getStruc()), &RAM_DATABASE);
        for (int i = 0; i < ids.size(); i++) {
            for (int l = 0; l < ids.at(i).size(); l++) {
                for (int j = 0; j < DATABASE.size(); j++) {
                    iEntity *tmp;
                    if (this->DATABASE.at(j)->getStruc()->id == ids.at(i).at(l)) {
                        std::cout << "AVANT CALL COLLISION HANDLER" << std::endl;
                        tmp = this->DATABASE.at(j)->Collision_handler(ids, /*Remplacer par ram*/DATABASE, &id_generator);
                        if (tmp != NULL) {
                            std::cout << "BONUS RECEIVE HANDLER" << std::endl;
                            tmp->getStruc()->id = id_generator;
                            std::cout << id_generator << std::endl;
                            id_generator += 1;
                            std::cout << id_generator << std::endl;
/*                                std::cout << tampon->getStruc(). */
                            DATABASE.push_back(tmp);
                            tmp = NULL;
                        }
                    }
                }
            }
        }
        //Entities_to_update = Health.Health_handler(Hit_result);
        DATABASE_Update(Entities_to_update);
        RAM_DATABASE = RAM.RAM_handler(DATABASE);
    }
    if (DATABASE.at(healthCheck)->struc.health > 0) {
        if (type == 2) {
            int index_for_target_entity = this->Verify_ID(id);
            if (static_cast<Player *>(DATABASE.at(index_for_target_entity))->count == 0) {
                std::cout << "TYPE 2" << std::endl;
                s_Entity bullet;
                bullet.type = 4;
                bullet.underType = 1;
                bullet.id = id_generator++;
                bullet.health = 50;
                bullet.pos_x = pos_x + 100;
                bullet.pos_y = pos_y + 45;
                bullet.frame = 0;
                bullet.damage = 1;
                int decalY = 0;
                for (int i = 0; i < static_cast<Player *>(DATABASE.at(index_for_target_entity))->weapon && i < 2; i++) {
                    s_Entity rocket;
                    rocket.type = 4;
                    rocket.underType = 2;
                    rocket.id = id_generator++;
                    rocket.health = 50;
                    rocket.pos_x = pos_x + 20;
                    rocket.pos_y = pos_y + decalY;
                    rocket.frame = 0;
                    rocket.damage = 1;
                    decalY += 10;
                    Rocket *tmp = new Rocket(rocket, true);
                    DATABASE.push_back(tmp);
                }
                decalY = 0;
                int directionX = 10;
                int directionY = 10;
                int modX = 1;
                int modY = 1;
                for (int i = 0; i < static_cast<Player *>(DATABASE.at(index_for_target_entity))->bouncingBullet && i < 2; i++) {
                    s_Entity bBullet;
                    bBullet.type = 4;
                    bBullet.underType = 4;
                    bBullet.id = id_generator++;
                    bBullet.health = 50;
                    bBullet.pos_x = pos_x + 20;
                    bBullet.pos_y = pos_y + decalY;
                    bBullet.frame = 1;
                    bBullet.damage = 1;
                    BouncingBullet *tmp = new BouncingBullet(bBullet, true, modX, modY, directionX, directionY);
                    directionY -= 2;
                    DATABASE.push_back(tmp);
                }
                Bullet *tmp = new Bullet(bullet, true);
                DATABASE.push_back(tmp);
                static_cast<Player *>(DATABASE.at(index_for_target_entity))->count = static_cast<Player *>(DATABASE.at(index_for_target_entity))->maxCount;
            }
        }
    }
    //send
    std::cout << "________________FIN RECEIVE FROM CLIENT_____________________" << std::endl;

}

int ServerInternalLogic::Verify_ID(int id)
{
    int verif = 0;
    int index = 0;
    while (verif != DATABASE.size())
    {
        if (DATABASE.at(verif)->getStruc()->id == id) {
            index = verif;
            std::cout << "INDEX = " << index << std::endl;
            //usleep(15000000);
        }
        verif++;
    }
    return (index);
}

std::vector<s_Entity> ServerInternalLogic::getRam()
{
    return (this->RAM_DATABASE);
}