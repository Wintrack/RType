/*
** EPITECH PROJECT, 2022
** TEK3
** File description:
** Entity
*/

/**
 * @file Entity.cpp
 * @brief Entity function
 * @version 0.1
 * @date 2022-10-17
 *
 */

#include "../../include/game/Entity.hpp"
#include "raylib.h"

Player::Player(s_Entity entity)
{
    struc.type = entity.type;
    struc.id = entity.id;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.underType = entity.underType;
    struc.pos_x = (float)entity.pos_x;
    struc.pos_y = (float)entity.pos_y;
    struc.frame = entity.frame;
    struc.i_frame = 0;
    weapon = 0;
    bouncingBullet = 0;
    maxCount = 30;
    count = 0;
    mod = 1;
    isDead = false;
}

Player::~Player()
{
    //UnloadTexture(sprite);
}

void Player::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *>Player::Movement_handler(std::vector<iEntity *>)
{
    std::cout << "PLAYER MOVEMENT HANDLER" << std::endl;
    if (count > 0) {
        count--;
    }
    return (static_cast<std::vector<iEntity *>>(NULL));
}

iEntity *Player::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "______________PLAYER COLLISION SYS_____________" << std::endl;
    for (int i = 0; i < ids.size(); i++) {
        for (int j = 0; j < ids.at(i).size(); j++) {
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            for (int l = 0; l < ram.size(); l++) {
                if (struc.health > 0) { 
                    if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                        if (ram.at(l)->struc.type == 2) {
                            std::cout << "Player collides with enemy" << std::endl;
                            this->struc.health -= 15 * ram.at(l)->getStruc()->damage;
                            if (this->struc.i_frame <= 0) {
                                std::cout << "SET I_FRAME" << std::endl;
                                this->struc.i_frame = 40;
                            }
                        }
                        if (ram.at(l)->getStruc()->type == 5) {
                            std::cout << "Player collide with wall" << std::endl;
                            if (ram.at(l)->getStruc()->pos_x >= this->struc.pos_x) {
                                this->struc.pos_x -= 5;
                            }
                            if (ram.at(l)->getStruc()->pos_y >= this->struc.pos_y) {
                                this->struc.pos_y -= 5;
                            }
                        }
                        if (ram.at(l)->struc.type == 4) {
                            std::cout << "IF TYPE = 4" << std::endl;
                            if (ram.at(l)->struc.underType == 1) {
                                if (static_cast<Bullet *>(ram.at(l))->isAllied == false) {
                                    this->struc.health -= 10 * ram.at(l)->getStruc()->damage;
                                    if (this->struc.i_frame <= 0) {
                                        std::cout << "SET I_FRAME" << std::endl;
                                        this->struc.i_frame = 40;
                                    }
                                }
                            }
                            else if (ram.at(l)->struc.underType == 3) {
                                std::cout << "Player Collides with Laser. Health = " << struc.health << std::endl;
                                if (static_cast<Laser *>(ram.at(l))->isAllied == false) {
                                    this->struc.health -= 10 * ram.at(l)->getStruc()->damage;
                                    std::cout << "Health after damage = " << struc.health << " && dmg = " << ram.at(l)->getStruc()->damage << std::endl;
                                    if (this->struc.i_frame <= 0) {
                                        std::cout << "SET I_FRAME" << std::endl;
                                        this->struc.i_frame = 40;
                                    }
                                }
                            }
                        }
                        if (ram.at(l)->struc.type == 6) {
                            std::cout << "Player collides with enemy" << std::endl;
                            this->struc.health -= 40 * ram.at(l)->getStruc()->damage;
                            if (this->struc.i_frame <= 0) {
                                std::cout << "SET I_FRAME" << std::endl;
                                this->struc.i_frame = 40;
                            }
                        }
                        if (ram.at(l)->struc.type == 3) {
                            if (ram.at(l)->struc.underType == 1 && maxCount > 0) {
                                std::cout <<  "IF BONUS OUAIS" << std::endl;
                                maxCount -= 3;
                            }
                            else if (ram.at(l)->struc.underType == 2) {
                                std::cout <<  "IF WEAPON OUAIS" << std::endl;
                                weapon++;
                            }
                            else if (ram.at(l)->struc.underType == 3) {
                                std::cout <<  "IF HEALTH OUAIS" << std::endl;
                                struc.health += 20;
                            }
                            else if (ram.at(l)->struc.underType == 4) {
                                std::cout <<  "IF BB OUAIS" << std::endl;
                                bouncingBullet++;
                            }
                        }
                    }
                }
                if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                    if (ram.at(l)->struc.type == 3) {
                        if (ram.at(l)->struc.underType == 5) {
                            struc.health += 50;
                        }
                    }
                }
            }
        }
    }
}

void Player::Frame_handler()
{
    std::cout << "__________________FRAME PLAYER HANDLER__________________" << std::endl;
    int i = 0;
    std::cout << "I = " << i << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    getStruc()->frame += mod;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
    if (struc.health > 0) {
        if (isDead == true) {
            isDead = false;
            struc.frame = 0;
            mod = -1;
        }
        if (struc.frame >= 4 || struc.frame <= 0) {
            mod *= -1;
        }
    }
    else {
        if (isDead == false) {
            isDead = true;
            struc.frame = 5;
            mod = -1;
        }
        if (struc.frame >= 6 || struc.frame <= 5) {
            mod *= -1;
        }
    }
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME PLAYER HANDLER____________" << std::endl;
}

s_Entity *Player::getStruc()
{
    return (&struc);
    
}

Enemy::Enemy(s_Entity entity)
{
    struc.type = entity.type;
    struc.id = entity.id;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.pos_x = (float)entity.pos_x;
    struc.pos_y = (float)entity.pos_y;
    struc.underType = entity.underType;
    struc.frame = entity.frame;
    mod = 1;
}

Enemy::~Enemy()
{
    //UnloadTexture(sprite);
}

void Enemy::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *> Enemy::Movement_handler(std::vector<iEntity *>)
{
    std::cout << "\t\t\t_____Enemy movement_____" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    int sign2 = std::rand() % 2;
    if (sign2 == 1) {
        struc.pos_y += 10;
    }
    else {
        struc.pos_y -= 10;
    }
    struc.pos_x -= 5;
    std::cout << "\t\t\t___________" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::cout << "\t\t\t___fin Enemy movement___" << std::endl;
    return (static_cast<std::vector<iEntity *>>(NULL));
}

iEntity *Enemy::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "______________ENEMY COLLISION SYS_____________" << std::endl;
    for (int i = 0; i < ids.size(); i++) {
        //std::cout << "I = " << i << std::endl;
        for (int j = 0; j < ids.at(i).size(); j++) {
            //std::cout << "j = " << j << std::endl;
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            //std::cout << "j after if 2 = " << j << std::endl;
            for (int l = 0; l < ram.size(); l++) {
                //std::cout << "l = " << l << std::endl;
                if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                    if (ram.at(l)->struc.type == 4) {
                        if (static_cast<Bullet *>(ram.at(l))->isAllied == true) {
                            std::cout << "Enemy collides with bullet" << std::endl;
                            this->struc.health -= 1000;
                                std::cout << "IF RAND" << std::endl;
                                s_Entity tmp = {3, (std::rand() % 3) + 1, 0, 50, struc.pos_y, struc.pos_x, 0, 1, 0, false};
                                Bonus *entity = new Bonus(tmp);
                                return (entity);
//                            }
                        }
                    }
                }
            }
        }
    }
}

void Enemy::Frame_handler()
{
    std::cout << "__________________FRAME ENEMY HANDLER__________________" << std::endl;
    int i = 0;
    std::cout << "I = " << i << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    getStruc()->frame += mod;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
    if (struc.frame >= 5 || struc.frame <= 0) {
        mod *= -1;
    }
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME ENEMY HANDLER____________" << std::endl;
}

s_Entity *Enemy::getStruc()
{
    return (&struc);
}

ShootingEnemy::ShootingEnemy(s_Entity entity)
{
    struc.type = entity.type;
    struc.id = entity.id;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.pos_x = (float)entity.pos_x;
    struc.pos_y = (float)entity.pos_y;
    struc.underType = entity.underType;
    struc.frame = entity.frame;
    count = 10;
    mod = 1;
}

ShootingEnemy::~ShootingEnemy()
{
    //UnloadTexture(sprite);
}

void ShootingEnemy::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *> ShootingEnemy::Movement_handler(std::vector<iEntity *> ram)
{
    std::cout << "\t\t\t_____ShootingEnemy movement_____" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    int sign2 = std::rand() % 2;
    std::vector<iEntity *> ret;
    Bullet *bullet = NULL;
    if (sign2 == 1) {
        struc.pos_y += 10;
    }
    else {
        struc.pos_y -= 10;
    }
    struc.pos_x -= 5;
    if (struc.pos_x < 2000) {
        if (count == 0) {
            std::cout << "COUNT = 0 BULLET" << std::endl;
            s_Entity tmp = {4, 1, 0, 50 ,(struc.pos_y + 45), (struc.pos_x - 10), 0, 2, false};
            bullet = new Bullet(tmp, false);
            count = 100;
        }
        else {
            count--;
        }
    }
    ret.push_back(bullet);
    std::cout << "count = " << count << " && Sizeof = " << sizeof(bullet) << std::endl;
    std::cout << "\t\t\t___________" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::cout << "\t\t\t___fin ShootingEnemy movement___" << std::endl;
    return (ret);
}

iEntity *ShootingEnemy::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "______________ShootingENEMY COLLISION SYS_____________" << std::endl;
    for (int i = 0; i < ids.size(); i++) {
        //std::cout << "I = " << i << std::endl;
        for (int j = 0; j < ids.at(i).size(); j++) {
            //std::cout << "j = " << j << std::endl;
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            //std::cout << "j after if 2 = " << j << std::endl;
            for (int l = 0; l < ram.size(); l++) {
                //std::cout << "l = " << l << std::endl;
                if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                    if (ram.at(l)->struc.type == 4) {
                        std::cout << "First if collides bullet ShootingEnemy" << std::endl;
                        if (static_cast<Bullet *>(ram.at(l))->isAllied == true) {
                            std::cout << "ShootingEnemy collides with allied bullet" << std::endl;
                            this->struc.health -= 1000;
/*                             int rand = std::rand() % 100;
                            std::cout << "RAND = " << rand << std::endl;
                            if (rand <= 34) { */
                                std::cout << "IF RAND" << std::endl;
                                s_Entity tmp = {3, (std::rand() % 3) + 1, 0, 50, struc.pos_y, struc.pos_x, 0, 1, 0, false};
                                Bonus *entity = new Bonus(tmp);
                                return (entity);
/*                             } */
                        }
                    }
                }
            }
        }
    }
}

void ShootingEnemy::Frame_handler()
{
    std::cout << "__________________FRAME Shooting HANDLER__________________" << std::endl;
    int i = 0;
    std::cout << "I = " << i << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
    getStruc()->frame += mod;
    if (struc.frame >= 5 || struc.frame <= 0) {
        mod *= -1;
    }
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME Shooting HANDLER____________" << std::endl;
}

s_Entity *ShootingEnemy::getStruc()
{
    return (&struc);
}

Bonus::Bonus(s_Entity entity)
{
    struc.type = entity.type;
    struc.id = entity.id;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.pos_x = (float)entity.pos_x;
    struc.pos_y = (float)entity.pos_y;
    struc.underType = entity.underType;
    struc.frame = entity.frame;
    mod = 1;
}

Bonus::~Bonus()
{
    //UnloadTexture(sprite);
}

void Bonus::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *> Bonus::Movement_handler(std::vector<iEntity *> ram)
{
    std::cout << "\t\t\t_____Bonus movement_____" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::cout << "\t\t\t___________" << std::endl;
    struc.pos_x -= 5;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::cout << "\t\t\t___fin Bonus movement___" << std::endl;
    return (static_cast<std::vector<iEntity *>>(NULL));
}

iEntity *Bonus::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "______________Bonus COLLISION SYS_____________" << std::endl;
    for (int i = 0; i < ids.size(); i++) {
        //std::cout << "I = " << i << std::endl;
        for (int j = 0; j < ids.at(i).size(); j++) {
            //std::cout << "j = " << j << std::endl;
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            //std::cout << "j after if 2 = " << j << std::endl;
            for (int l = 0; l < ram.size(); l++) {
                //std::cout << "l = " << l << std::endl;
                if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                    if (ram.at(l)->struc.type == 4) {
                        if (static_cast<Bullet *>(ram.at(l))->isAllied == true) {
                        std::cout << "Bonus collides with allied bullet" << std::endl;
                        this->struc.health -= 1000;
                        }
                    }
                    if (ram.at(l)->struc.type == 1) {
                        std::cout << "Bonus collides with player" << std::endl;
                        this->struc.health -= 1000;
                    }
                }
            }
        }
    }
}

void Bonus::Frame_handler()
{
    std::cout << "__________________FRAME Bonus HANDLER__________________" << std::endl;
    int i = 0;
    std::cout << "I = " << i << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
    getStruc()->frame += mod;
    if (struc.frame >= 4 || struc.frame <= 0) {
        mod *= -1;
    }
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME Bonus HANDLER____________" << std::endl;
}

s_Entity *Bonus::getStruc()
{
    return (&struc);
}

Bullet::Bullet(s_Entity entity, bool b)
{
    isAllied = b;
    struc.type = entity.type;
    struc.id = entity.id;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.pos_x = (float)entity.pos_x;
    struc.pos_y = (float)entity.pos_y;
    struc.underType = entity.underType;
    struc.frame = entity.frame;
    mod = 1;
}

Bullet::~Bullet()
{
    //UnloadTexture(sprite);
}

void Bullet::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *> Bullet::Movement_handler(std::vector<iEntity *> ram)
{
/*     int sign = std::rand() % 2;
    if (sign == 1) {
        struc.pos_y += 10;
    }
    else {
        struc.pos_y -= 10;
    } */
    if (isAllied)
        struc.pos_x += 10;
    else 
        struc.pos_x -= 10;
    return (static_cast<std::vector<iEntity *>>(NULL));
}

iEntity *Bullet::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "Bullet collision sys" << std::endl;
    for (int i = 0; i < ids.size(); i++) {
        for (int j = 0; j < ids.at(i).size(); j++) {
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            for (int l = 0; l < ram.size(); l++) {
                if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                    if (ram.at(l)->getStruc()->type == 2 && isAllied == true) {
                        std::cout << "Bullet collides with enemy" << std::endl;
                        this->struc.health -= 50;
                    }
                    if (ram.at(l)->getStruc()->type == 5) {
                        std::cout << "bullet collides with wall" << std::endl;
                        this->struc.health -= 50;
                    }
                    if (ram.at(l)->getStruc()->type == 1 && isAllied == false) {
                        std::cout << "bullet collides with wall" << std::endl;
                        this->struc.health -= 50;
                    }
                }
            }
        }
    }
    return (NULL);
}

void Bullet::Frame_handler()
{
    std::cout << "__________________FRAME BULLEt HANDLER__________________" << std::endl;
    int i = 0;
    std::cout << "I = " << i << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    getStruc()->frame += mod;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
    if (struc.frame >= 5 || struc.frame <= 0) {
        mod *= -1;
    }
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME BULLET HANDLER____________" << std::endl;
}

s_Entity *Bullet::getStruc()
{
    return (&struc);
}

Bloc::Bloc(s_Entity entity)
{
    struc.type = entity.type;
    struc.id = entity.id;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.pos_x = (float)entity.pos_x;
    struc.pos_y = (float)entity.pos_y;
    struc.underType = entity.underType;
    struc.frame = entity.frame;
}

Bloc::~Bloc()
{
    //UnloadTexture(sprite);
}

void Bloc::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *>Bloc::Movement_handler(std::vector<iEntity *> ram)
{
    struc.pos_x -= 10;
    return (static_cast<std::vector<iEntity *>>(NULL));
}

iEntity *Bloc::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "____________Bloc collision sys______________" << std::endl;
    return (NULL);
}

void Bloc::Frame_handler()
{
    std::cout << "__________________FRAME BLOC HANDLER__________________" << std::endl;
/*     int i = 0;
    std::cout << "I = " << i << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    getStruc()->frame += mod;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
    if (struc.frame >= 5 || struc.frame <= 0) {
        mod *= -1;
    }
    std::cout << "___________________________" << std::endl;
    if (struc.i_frame != 0) {
        struc.i_frame--;
    } */
    std::cout << "______________FIN FRAME BLOC HANDLER____________" << std::endl;
}

s_Entity *Bloc::getStruc()
{
    return (&struc);
}

Weapon::Weapon(s_Entity entity)
{
    struc.type = entity.type;
    struc.id = entity.id;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.pos_x = (float)entity.pos_x;
    struc.pos_y = (float)entity.pos_y;
    struc.underType = entity.underType;
    struc.frame = entity.frame;
    mod = 1;
}

Weapon::~Weapon()
{
    //UnloadTexture(sprite);
}

void Weapon::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *> Weapon::Movement_handler(std::vector<iEntity *> ram)
{
    std::cout << "\t\t\t_____Weapon movement_____" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::cout << "\t\t\t___________" << std::endl;
    struc.pos_x -= 5;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::cout << "\t\t\t___fin Weapon movement___" << std::endl;
    return (static_cast<std::vector<iEntity *>>(NULL));
}

iEntity *Weapon::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "______________Weapon COLLISION SYS_____________" << std::endl;
    for (int i = 0; i < ids.size(); i++) {
        //std::cout << "I = " << i << std::endl;
        for (int j = 0; j < ids.at(i).size(); j++) {
            //std::cout << "j = " << j << std::endl;
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            //std::cout << "j after if 2 = " << j << std::endl;
            for (int l = 0; l < ram.size(); l++) {
                //std::cout << "l = " << l << std::endl;
                if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                    if (ram.at(l)->struc.type == 4) {
                        if (static_cast<Bullet *>(ram.at(l))->isAllied == true) {
                        std::cout << "Weapon collides with allied bullet" << std::endl;
                        this->struc.health -= 1000;
                        }
                    }
                    if (ram.at(l)->struc.type == 1) {
                        std::cout << "Weapon collides with player" << std::endl;
                        this->struc.health -= 1000;
                    }
                }
            }
        }
    }
}

void Weapon::Frame_handler()
{
    std::cout << "__________________FRAME Weapon HANDLER__________________" << std::endl;
    int i = 0;
    std::cout << "I = " << i << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
    getStruc()->frame += mod;
    if (struc.frame >= 4 || struc.frame <= 0) {
        mod *= -1;
    }
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME Weapon HANDLER____________" << std::endl;
}

s_Entity *Weapon::getStruc()
{
    return (&struc);
}

Rocket::Rocket(s_Entity entity, bool b)
{
    struc.type = entity.type;
    struc.id = entity.id;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.pos_x = (float)entity.pos_x;
    struc.pos_y = (float)entity.pos_y;
    struc.underType = entity.underType;
    struc.frame = entity.frame;
    isAllied = b;
    mod = 1;
}

Rocket::~Rocket()
{
    //UnloadTexture(sprite);
}

void Rocket::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *> Rocket::Movement_handler(std::vector<iEntity *> ram)
{
    std::cout << "\t\t\t_____Rocket movement_____" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::cout << "\t\t\t___________" << std::endl;
    std::vector<iEntity *> square;
    int bestPosX = 0;
    int tempPosY = 0;
    int tempPosX = 0;
    for (int i = 0; i < ram.size(); i++) {
        if (isAllied == true) {
            if ((ram.at(i)->getStruc()->type == 2 || ram.at(i)->getStruc()->type == 6) && ram.at(i)->getStruc()->pos_x <= struc.pos_x + width + 200 && ram.at(i)->getStruc()->pos_x + ram.at(i)->width 
            && ram.at(i)->getStruc()->pos_y <= struc.pos_y + 100 && (ram.at(i)->getStruc()->pos_y + ram.at(i)->height) >= struc.pos_y - 100) {
                square.push_back(ram.at(i));
                std::cout << "square.at(" << i << ").id = " << ram.at(i)->struc.id << " && this.id = " << struc.id << std::endl;  
            }
        } else if (isAllied == false) {
            if (ram.at(i)->getStruc()->type == 1 && ram.at(i)->getStruc()->pos_x <= struc.pos_x + width + 200 && ram.at(i)->getStruc()->pos_x + ram.at(i)->width >= struc.pos_x 
            && ram.at(i)->getStruc()->pos_y <= struc.pos_y + 100 && (ram.at(i)->getStruc()->pos_y + ram.at(i)->height) >= struc.pos_y - 100) {
                square.push_back(ram.at(i));
            }
        }
    }
    if (square.size() > 0) {
        for (int j = 0; j < square.size(); j++) {
            if ((square.at(j)->getStruc()->pos_x - struc.pos_x) > bestPosX) {
                bestPosX = (square.at(j)->getStruc()->pos_x - struc.pos_x);
                tempPosX = square.at(j)->getStruc()->pos_x;
                tempPosY = square.at(j)->getStruc()->pos_y;
            }
        }
        std::cout << "_____Print before for____" << std::endl;
        if (struc.pos_y < tempPosY) {
            struc.pos_y += 10;
        }
        if (struc.pos_x < tempPosX) {
            struc.pos_x += 10;
        }
        if (struc.pos_y > tempPosY) {
            struc.pos_y -= 10;
        }
    }
    else {
        struc.pos_x += 10;
    }
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::cout << "\t\t\t___fin Rocket movement___" << std::endl;
    return (static_cast<std::vector<iEntity *>>(NULL));
}

iEntity *Rocket::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "______________Rocket COLLISION SYS_____________" << std::endl;
    for (int i = 0; i < ids.size(); i++) {
        //std::cout << "I = " << i << std::endl;
        for (int j = 0; j < ids.at(i).size(); j++) {
            //std::cout << "j = " << j << std::endl;
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            //std::cout << "j after if 2 = " << j << std::endl;
            for (int l = 0; l < ram.size(); l++) {
                //std::cout << "l = " << l << std::endl;
                if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                    if (ram.at(l)->struc.type == 4) {
                        if (static_cast<Bullet *>(ram.at(l))->isAllied == true && isAllied == false) {
                            std::cout << "Enemy Rocket collides with allied bullet" << std::endl;
                            this->struc.health -= 1000;
                        }
                        if (static_cast<Bullet *>(ram.at(l))->isAllied == false && isAllied == true) {
                            std::cout << "Allied Rocket collides with Enemy bullet" << std::endl;
                            this->struc.health -= 1000;
                        }
                    }

                    if (ram.at(l)->struc.type == 1 && isAllied == false) {
                        std::cout << "Enemy Rocket collides with player" << std::endl;
                        this->struc.health -= 1000;
                    }
                }
            }
        }
    }
    if (struc.pos_x > 2000 || struc.pos_x < -50 || struc.pos_y < -50 || struc.pos_y > 1200) {
        this->struc.health -= 1000;     
    }
    std::cout << "______________Rocket COLLISION SYS_____________" << std::endl;
    return (NULL);
}

void Rocket::Frame_handler()
{
    std::cout << "__________________FRAME Rocket HANDLER__________________" << std::endl;
    int i = 0;
    std::cout << "I = " << i << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
    getStruc()->frame += mod;
    if (struc.frame >= 4 || struc.frame <= 0) {
        mod *= -1;
    }
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME Rocket HANDLER____________" << std::endl;
}

s_Entity *Rocket::getStruc()
{
    return (&struc);
}

ComposedEnemy::ComposedEnemy(std::vector<s_Entity> entity)
{
    struc.type = entity.at(0).type;
    struc.underType = entity.at(0).underType;
    struc.id = entity.at(0).id;
    struc.health = entity.at(0).health;
    struc.pos_y = entity.at(0).pos_y;
    struc.pos_x = entity.at(0).pos_x;
    struc.frame = entity.at(0).frame;
    struc.damage = entity.at(0).damage;
    std::cout << "Composed type = " << struc.type << std::endl;
    std::cout << "Composed underType = " << struc.underType << std::endl;
    direction_x = -10;
    direction_y = 10;
    count = 60;
    std::cout << "__________LOOP___________" << std::endl;
    for(int i = 1; i < entity.size(); i++) {
        std::cout << i << std::endl;
        PARTS.push_back(entity.at(i));
    }
    mod = 1;
    std::cout << "__________FIN CONSTRUCTEUR COMPOSED___________" << std::endl;
}

ComposedEnemy::~ComposedEnemy()
{
    //UnloadTexture(sprite);
}

void ComposedEnemy::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *> ComposedEnemy::Movement_handler(std::vector<iEntity *>)
{
    std::cout << "\t\t\t_____ComposedEnemy movement_____" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    int exPos_x = 0;
    int exPos_y = 0;
    int exPos_x2 = 0;
    int exPos_y2 = 0;
    if (struc.pos_x == (1920 - (90 * (PARTS.size() + 1)))) {
        direction_x = -10;
    }
    if (struc.pos_x == 0) {
        direction_x = 10;
    }
    struc.pos_x += direction_x;
    exPos_x = struc.pos_x + 90;
    exPos_y = struc.pos_y;
    for (int i = 0; i < PARTS.size() ; i++) {
        exPos_x2 = PARTS.at(i).pos_x + 90;
        PARTS.at(i).pos_x = exPos_x;
        exPos_x = exPos_x2;
        exPos_y2 = PARTS.at(i).pos_y;
        PARTS.at(i).pos_y =  exPos_y;
        exPos_y = exPos_y2;
    }    
    if ((struc.pos_y + 90) >= 1080) {
        direction_y = -10;
    }
    if (struc.pos_y <= 0) {
        direction_y = 10;
    }
    struc.pos_y += direction_y;
    /*PARTS.at(0).pos_x = struc.pos_x + width;
    PARTS.at(0).pos_y = struc.pos_y + height;
    if (struc.pos_x == 1920) {
        direction_x = -10;
    }
    if (struc.pos_x == 0) {
        direction_x = 10;
    }
    if (count == 0) {
        direction_y *= -1;
        count = 20;
    } else count--;
    struc.pos_x += direction_x;
    if (struc.pos_y > 0 && struc.pos_y < 1080)
        struc.pos_y += direction_y;
    std::cout << "\t\t\t___________" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::cout << "\t\t\t___fin ComposedEnemy movement___" << std::endl;*/
    return (static_cast<std::vector<iEntity *>>(NULL));
}

iEntity *ComposedEnemy::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "______________ComposedEnemy COLLISION SYS_____________" << std::endl;
    for (int i = 0; i < ids.size(); i++) {
        std::cout << "I = " << i << std::endl;
        for (int j = 0; j < ids.at(i).size(); j++) {
            std::cout << "j = " << j << std::endl;
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            std::cout << "j after if 2 = " << j << std::endl;
            for (int l = 0; l < ram.size(); l++) {
                std::cout << "l = " << l << std::endl;
                if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                    if (ram.at(l)->struc.type == 4) {
                        if (static_cast<Bullet *>(ram.at(l))->isAllied == true) {
                            std::cout << "ComposedEnemy collides with bullet" << std::endl;
                            this->struc.health -= 15 * ram.at(l)->getStruc()->damage;
                        }
                    }
                }
                std::cout << "APRES COLLISION HEAD" << std::endl;
                for (int k = 0; k < PARTS.size(); k++) {
                    if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                        if (ram.at(l)->struc.type == 4) {
                            if (static_cast<Bullet *>(ram.at(l))->isAllied == true) {
                                std::cout << "ComposedEnemy collides with bullet" << std::endl;
                                this->PARTS.at(k).health -= 15 * ram.at(l)->getStruc()->damage;
                            }
                        }
                    }  
                }
                std::cout << "APRES COLLISION PARTS" << std::endl;
            }
        }
    }
    return (NULL);
}

void ComposedEnemy::Frame_handler()
{
    std::cout << "__________________FRAME ComposedEnemy HANDLER__________________" << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    //getStruc()->frame += mod;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
/*     if (struc.frame >= 5 || struc.frame <= 0) {
        mod *= -1;
    } */
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME ComposedEnemy HANDLER____________" << std::endl;
}

s_Entity *ComposedEnemy::getStruc()
{
    return (&struc);
}

Boss::Boss(std::vector<s_Entity> entity)
{
    struc.type = entity.at(0).type;
    struc.underType = entity.at(0).underType;
    struc.id = entity.at(0).id;
    struc.health = entity.at(0).health;
    struc.pos_y = entity.at(0).pos_y;
    struc.pos_x = entity.at(0).pos_x;
    struc.frame = entity.at(0).frame;
    struc.damage = entity.at(0).damage;
    std::cout << "Boss type = " << struc.type << std::endl;
    std::cout << "Boss underType = " << struc.underType << std::endl;
    direction_x = -10;
    direction_y = 10;
    direction_ypart1 = 5;
    direction_ypart2 = 5;
    count = 5;
    countCanon1 = -1;
    countCanon2 = -1;
    countShooting1 = 300;
    countShooting2 = 2;
    countPhase2 = 100;
    spacingBullet = 0;
    phase = 1;
    std::cout << "__________LOOP___________" << std::endl;
    for(int i = 1; i < entity.size(); i++) {
        std::cout << i << std::endl;
        PARTS.push_back(entity.at(i));
    }
    mod = 1;
    std::cout << "__________FIN CONSTRUCTEUR BOSS___________" << std::endl;
}

Boss::~Boss()
{
    //UnloadTexture(sprite);
}

void Boss::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *>Boss::Movement_handler(std::vector<iEntity *>)
{
    std::cout << "\t\t\t_____Boss movement_____" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::vector<iEntity *> ret;
    int exPos_x = 0;
    int exPos_y = 0;
    int exPos_x2 = 0;
    int exPos_y2 = 0;
    int nb_parts_dead = 0;
    if (phase == 1) {
        if (count == 0) {
            direction_y *= -1;
            count = 10;
        } else count--;
        if (struc.pos_x >= 1750) {
            struc.pos_x -= 10;
            for (int i = 0; i < PARTS.size(); i++) {
                PARTS.at(i).pos_x -= 10;
            }
        } else {
            countCanon1 = 100;
            countCanon2 = 100;
        }
        for (int i = 0; i < PARTS.size(); i++) {
            if (PARTS.at(i).health > 0) {
                if (PARTS.at(i).pos_y == 50 || PARTS.at(i).pos_y == 500) {
                    direction_ypart1 *= -1;
                }
                if ((PARTS.at(i).pos_y == 540 || PARTS.at(i).pos_y == 900)) {
                    direction_ypart2 *= -1;
                }
                if (PARTS.at(i).pos_y >= 50 && PARTS.at(i).pos_y <= 500) {
                    std::cout << "MOVE PART DU HAUT" << std::endl;
                    PARTS.at(i).pos_y += direction_ypart1;
                }
                if ((PARTS.at(i).pos_y >= 540 && PARTS.at(i).pos_y <= 900)) {
                    std::cout << "MOVE PART DU BAS" << std::endl;
                    PARTS.at(i).pos_y += direction_ypart2;
                }
                if (countShooting1 <= 0) {
                    s_Entity laser = {4, 3, 0, 50, PARTS.at(i).pos_y, PARTS.at(i).pos_x - 100, 0, 4, 0, false};
                    Laser *tmp = new Laser(laser, false);
                    ret.push_back(tmp);
                    int shootMod = std::rand() % 150;
                    countShooting1 = 200 + shootMod;
                } else countShooting1--;
            } else {
                nb_parts_dead++;
                std::cout << "NB_PARTS_DEAD = " << nb_parts_dead << std::endl;
            }
        }
        if (nb_parts_dead == PARTS.size()) {
            std::cout << "CHANGEMENT DE PHASE" << std::endl;
            phase++;
        }
    }
    if (phase == 2) {
        if (struc.pos_x + width >= 1920) {
            direction_x = -10;
        }
        if (struc.pos_x <= 0) {
            direction_x = 10;
        }
        struc.pos_x += direction_x;
/*         exPos_x = struc.pos_x + 90;
        exPos_y = struc.pos_y;
        for (int i = 0; i < PARTS.size() ; i++) {
            exPos_x2 = PARTS.at(i).pos_x + 90;
            PARTS.at(i).pos_x = exPos_x;
            exPos_x = exPos_x2;
            exPos_y2 = PARTS.at(i).pos_y;
            PARTS.at(i).pos_y =  exPos_y;
            exPos_y = exPos_y2;
        }     */
/*         if (count == 0) {
            direction_y *= -1;
            count = 60;
        } else count--; */
        if (struc.pos_y >= 1080) {
            direction_y = -10;
        }
        if (struc.pos_y + height <= 0) {
            direction_y = 10;
        }
        struc.pos_y += direction_y;
        if (countPhase2 <= 0) {
            s_Entity tmp = {4, 1, 0, 50, struc.pos_y - (height / 2) + spacingBullet, struc.pos_x - 20, 0, 3, 0, false};
            spacingBullet += 5;
            Bullet *bullet = new Bullet(tmp, false);
            ret.push_back(bullet);
            if (countPhase2 == -20) {
                int randMod = std::rand() % 50;
                countPhase2 = 75 + randMod;
                spacingBullet = 0;
            }
            countPhase2--;
        } else countPhase2--;
    }
    /*PARTS.at(0).pos_x = struc.pos_x + width;
    PARTS.at(0).pos_y = struc.pos_y + height;
    if (struc.pos_x == 1920) {
        direction_x = -10;
    }
    if (struc.pos_x == 0) {
        direction_x = 10;
    }
    if (count == 0) {
        direction_y *= -1;
        count = 20;
    } else count--;
    struc.pos_x += direction_x;
    if (struc.pos_y > 0 && struc.pos_y < 1080)
        struc.pos_y += direction_y;
    std::cout << "\t\t\t___________" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::cout << "\t\t\t___fin Boss movement___" << std::endl;*/
/*     for (int i = this->PARTS.size() - 1; i > 1 ; i--) {
        PARTS.at(i).pos_x = PARTS.at(i - 1).pos_x + width;
        PARTS.at(i).pos_y = PARTS.at(i - 1).pos_y;
    }
    PARTS.at(0).pos_x = struc.pos_x + width;
    PARTS.at(0).pos_y = struc.pos_y + height;
    if (struc.pos_x == 1920) {
        direction_x = -10;
    }
    if (struc.pos_x == 0) {
        direction_x = 10;
    }
    struc.pos_x += direction_x;
    //if (struc.pos_y > 0 && struc.pos_y < 1080)
     //   struc.pos_y += direction_y; */
    //return (NULL);
    return (ret);
}

iEntity *Boss::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "______________Boss COLLISION SYS_____________" << std::endl;
    for (int i = 0; i < ids.size(); i++) {
        std::cout << "I = " << i << std::endl;
        for (int j = 0; j < ids.at(i).size(); j++) {
            std::cout << "j = " << j << std::endl;
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            std::cout << "j after if 2 = " << j << std::endl;
            for (int l = 0; l < ram.size(); l++) {
                std::cout << "l = " << l << std::endl;
                if (ram.at(l)->struc.id == ids.at(i).at(j) && PARTS.size() == 0) {
                    if (ram.at(l)->struc.type == 4) {
                        if (static_cast<Bullet *>(ram.at(l))->isAllied == true) {
                            std::cout << "Boss collides with bullet" << std::endl;
                            this->struc.health -= 15 * ram.at(l)->getStruc()->damage;
                        }
                    }
                }
                std::cout << "APRES COLLISION HEAD" << std::endl;
/*                 for (int k = 0; k < PARTS.size(); k++) {
                    if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                        if (ram.at(l)->struc.type == 4) {
                            if (static_cast<Bullet *>(ram.at(l))->isAllied == true) {
                                std::cout << "Boss part" << k << "collides with bullet" << std::endl;
                                this->PARTS.at(k).health -= 15 * ram.at(l)->getStruc()->damage;
                            }
                        }
                    }  
                }
                std::cout << "APRES COLLISION PARTS" << std::endl; */
            }
        }
    }
    return (NULL);
}

void Boss::Frame_handler()
{
    std::cout << "__________________FRAME Boss HANDLER__________________" << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
    if (phase == 1) {
        struc.frame += this->mod;
        if (struc.frame >= 1 || struc.frame <= 0) {
            this->mod *= -1;
        }
    }
    else {
        struc.frame = 2;
    }
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME Boss HANDLER____________" << std::endl;
}

s_Entity *Boss::getStruc()
{
    return (&struc);
}

Laser::Laser(s_Entity entity, bool b)
{
    isAllied = b;
    struc.type = entity.type;
    struc.id = entity.id;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.pos_x = (float)entity.pos_x;
    struc.pos_y = (float)entity.pos_y;
    struc.underType = entity.underType;
    struc.frame = entity.frame;
    count = 500;
    mod = 1;
}

Laser::~Laser()
{
    //UnloadTexture(sprite);
}

void Laser::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *> Laser::Movement_handler(std::vector<iEntity *> ram)
{
/*     int sign = std::rand() % 2;
    if (sign == 1) {
        struc.pos_y += 10;
    }
    else {
        struc.pos_y -= 10;
    } */
    if (count == 0) {
        if (isAllied)
            struc.pos_x += 50;
        else {
            struc.pos_x -= 50;
            std::cout << "MOUVEMENT LASER ID = " << struc.id << " POS X = " << struc.pos_x << " WIDTH = " << width << std::endl;
        }
    } else {
        if (struc.pos_x > 0) {
            struc.pos_x -= 25;
        }
        count --;
    }
    return (static_cast<std::vector<iEntity *>>(NULL));
}

iEntity *Laser::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "Laser collision sys" << std::endl;
/*     for (int i = 0; i < ids.size(); i++) {
        for (int j = 0; j < ids.at(i).size(); j++) {
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            for (int l = 0; l < ram.size(); l++) {
                if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                    if (ram.at(l)->getStruc()->type == 2 && isAllied == true) {
                        std::cout << "Laser collides with enemy" << std::endl;
                        this->struc.health -= 50;
                    }
                    if (ram.at(l)->getStruc()->type == 5) {
                        std::cout << "Laser collides with wall" << std::endl;
                        this->struc.health -= 50;
                    }
                    if (ram.at(l)->getStruc()->type == 1 && isAllied == false) {
                        std::cout << "Laser collides with wall" << std::endl;
                        this->struc.health -= 50;
                    }
                }
            }
        }
    } */
    if ((struc.pos_x + 1920) < 0) {
        struc.health -= 100;
    }
    return (NULL);
}

void Laser::Frame_handler()
{
    std::cout << "__________________FRAME Laser HANDLER__________________" << std::endl;
/*     std::cout << "I = " << i << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    getStruc()->frame += mod;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
    if (struc.frame >= 5 || struc.frame <= 0) {
        mod *= -1;
    } */
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME Laser HANDLER____________" << std::endl;
}

s_Entity *Laser::getStruc()
{
    return (&struc);
}


Dummy::Dummy(s_Entity entity)
{
    struc.type = entity.type;
    struc.id = entity.id;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.pos_x = (float)entity.pos_x;
    struc.pos_y = (float)entity.pos_y;
    struc.underType = entity.underType;
    struc.frame = entity.frame;
    width = 62;
    height = 40;
    mod = 1;
}

Dummy::~Dummy()
{
    //UnloadTexture(sprite);
}

void Dummy::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *> Dummy::Movement_handler(std::vector<iEntity *> ram)
{
    std::cout << "\t\t\t_____Dummy movement_____" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::cout << "\t\t\t___________" << std::endl;
    struc.pos_x -= 5;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::cout << "\t\t\t___fin Dummy movement___" << std::endl;
    return (static_cast<std::vector<iEntity *>>(NULL));
}

iEntity *Dummy::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "______________Dummy COLLISION SYS_____________" << std::endl;
    for (int i = 0; i < ids.size(); i++) {
        //std::cout << "I = " << i << std::endl;
        for (int j = 0; j < ids.at(i).size(); j++) {
            //std::cout << "j = " << j << std::endl;
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            //std::cout << "j after if 2 = " << j << std::endl;
            for (int l = 0; l < ram.size(); l++) {
                //std::cout << "l = " << l << std::endl;
                if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                    if (ram.at(l)->struc.type == 4) {
                        if (static_cast<Bullet *>(ram.at(l))->isAllied == true) {
                        std::cout << "Dummy collides with allied bullet" << std::endl;
                        this->struc.health -= 1000;
                        }
                    }
                    if (ram.at(l)->struc.type == 1) {
                        std::cout << "Dummy collides with player" << std::endl;
                        this->struc.health -= 1000;
                    }
                }
            }
        }
    }
}

void Dummy::Frame_handler()
{
    std::cout << "__________________FRAME Dummy HANDLER__________________" << std::endl;
    int i = 0;
    std::cout << "I = " << i << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
    getStruc()->frame += mod;
    if (struc.frame >= 4 || struc.frame <= 0) {
        mod *= -1;
    }
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME Dummy HANDLER____________" << std::endl;
}

s_Entity *Dummy::getStruc()
{
    return (&struc);
}

BouncingBullet::BouncingBullet(s_Entity entity, bool b, int modX, int modY, int dirX, int dirY) : Bullet(entity, b) 
{
    isAllied = b;
    this->modX = modX;
    this->modY = modY;
    directionX = dirX;
    directionY = dirY;
    rebond = 0;
    mod = 1;
}

BouncingBullet::~BouncingBullet()
{
    //UnloadTexture(sprite);
}

void BouncingBullet::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *> BouncingBullet::Movement_handler(std::vector<iEntity *> ram)
{
    if (struc.pos_x + width >= 1920 || struc.pos_x <= 0) {
        modX *= -1;
        rebond++;
    }
    if (struc.pos_y + height >= 1080 || struc.pos_y <= 0) {
        modY *= -1;
        rebond++;
    }
    struc.pos_x += directionX * modX;
    struc.pos_y += directionY * modY;
    if (rebond >= 3) {
        this->struc.health -= 50;
    }
    return (static_cast<std::vector<iEntity *>>(NULL));
}

iEntity *BouncingBullet::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "BouncingBullet collision sys" << std::endl;
    for (int i = 0; i < ids.size(); i++) {
        for (int j = 0; j < ids.at(i).size(); j++) {
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            for (int l = 0; l < ram.size(); l++) {
                if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                    if (ram.at(l)->getStruc()->type == 2 && isAllied == true) {
                        std::cout << "BouncingBullet collides with enemy" << std::endl;
                        this->struc.health -= 50;
                    }
                    if (ram.at(l)->getStruc()->type == 5) {
                        std::cout << "Bouncingbullet collides with wall" << std::endl;
                        this->struc.health -= 50;
                    }
                    if (ram.at(l)->getStruc()->type == 1 && isAllied == false) {
                        std::cout << "Bouncingbullet collides with player" << std::endl;
                        this->struc.health -= 50;
                    }
                }
            }
        }
    }
    return (NULL);
}

void BouncingBullet::Frame_handler()
{
    std::cout << "__________________FRAME BouncingBULLEt HANDLER__________________" << std::endl;
    int i = 0;
    std::cout << "I = " << i << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
//    getStruc()->frame += mod;
    if ((modX == 1 && modY == -1) || (modX == -1 && modY == 1)) {
        struc.frame = 0;
    } else if ((modX == -1 && modY == -1) || (modX == 1 && modY == 1)) {
        struc.frame = 1;
    }

    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
/*     if (struc.frame >= 5 || struc.frame <= 0) {
        mod *= -1;
    } */
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME BouncingBULLET HANDLER____________" << std::endl;
}

s_Entity *BouncingBullet::getStruc()
{
    return (&struc);
}

Sol::Sol(s_Entity entity)
{
    struc.type = entity.type;
    struc.underType = entity.underType;
    struc.id = entity.id;
    struc.health = entity.health;
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.frame = entity.frame;
    struc.damage = entity.damage;
    std::cout << "Sol type = " << struc.type << std::endl;
    std::cout << "Sol underType = " << struc.underType << std::endl;
    direction_x = -10;
    direction_y = -10;
    count = 200;
    countCanon1 = -1;
    countShooting1 = 300;
    countPhase2 = 100;
    spacingBullet = 0;
    phase = 1;
    mod = 1;
    modX = 1;
    decal = 100;
    metronome = 0;
    lunaSpawn = false;
    std::cout << "__________FIN CONSTRUCTEUR Sol___________" << std::endl;
}

Sol::~Sol()
{
    //UnloadTexture(sprite);
}

void Sol::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *>Sol::Movement_handler(std::vector<iEntity *>)
{
    std::cout << "\t\t\t_____Sol movement_____" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::vector<iEntity *> ret;
    if (metronome == 0 && struc.pos_y > 100) {
        struc.pos_y -= 10;
    }
    else {
        if (struc.pos_y == 100 && struc.pos_x > 900) {
            metronome = 1;
        }
        else if (struc.pos_x == 100 && struc.pos_y == 100) {
            metronome = 2;
        }
        else if (struc.pos_y == 900 && struc.pos_x == 100) {
            metronome = 3;
        }
        else if (struc.pos_x == 1800 && struc.pos_y == 900) {
            metronome = 4;
        }
        switch (metronome)
        {
        case 1:
            struc.pos_x -= 10;
            break;
        case 2:
            struc.pos_y += 10;
            break;
        case 3:
            struc.pos_x += 10;
            break;
        case 4:
            struc.pos_y -= 10;
        default:
            break;
        }
    }
    if (struc.pos_x < 2000) {
        if (count <= 0) {
            std::cout << "COUNT = 0 BULLET" << std::endl;
            s_Entity tmp = {4, 1, 0, 50 ,(struc.pos_y + decal), (struc.pos_x - 10), 0, 2, false};
            Bullet *bullet = new Bullet(tmp, false);
            ret.push_back(bullet);
            decal -= 10;
            count--;
            if (count == -10) {
                decal = 100;
                int rand = std::rand() % 40;
                count = 20 + rand;
            }
        }
        else {
            count--;
        }
    }
    if (struc.health <= 300 && lunaSpawn == false) {
        s_Entity tmp = {6, 4, 0, 600, struc.pos_y, struc.pos_x, 0, 2, 0, false};
        Luna *luna = new Luna(tmp);
        ret.push_back(luna);
        lunaSpawn = true;
    }
    return (ret);
}

iEntity *Sol::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "______________Sol COLLISION SYS_____________" << std::endl;
    for (int i = 0; i < ids.size(); i++) {
        std::cout << "I = " << i << std::endl;
        for (int j = 0; j < ids.at(i).size(); j++) {
            std::cout << "j = " << j << std::endl;
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            std::cout << "j after if 2 = " << j << std::endl;
            for (int l = 0; l < ram.size(); l++) {
                std::cout << "l = " << l << std::endl;
                if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                    if (ram.at(l)->struc.type == 4) {
                        if (static_cast<Bullet *>(ram.at(l))->isAllied == true) {
                            std::cout << "Sol collides with bullet" << std::endl;
                            this->struc.health -= 15 * ram.at(l)->getStruc()->damage;
                        }
                    }
                }
                std::cout << "APRES COLLISION SOL" << std::endl;
            }
        }
    }
    return (NULL);
}

void Sol::Frame_handler()
{
    std::cout << "__________________FRAME Sol HANDLER__________________" << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
    if (phase == 1) {
        struc.frame += this->mod;
        if (struc.frame >= 1 || struc.frame <= 0) {
            this->mod *= -1;
        }
    }
    else {
        struc.frame = 2;
    }
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME Sol HANDLER____________" << std::endl;
}

s_Entity *Sol::getStruc()
{
    return (&struc);
}

Luna::Luna(s_Entity entity)
{
    struc.type = entity.type;
    struc.underType = entity.underType;
    struc.id = entity.id;
    struc.health = entity.health;
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.frame = entity.frame;
    struc.damage = entity.damage;
    std::cout << "Luna type = " << struc.type << std::endl;
    std::cout << "Luna underType = " << struc.underType << std::endl;
    direction_x = -10;
    direction_y = 10;
    count = 200;
    countCanon1 = -1;
    countShooting1 = 300;
    countPhase2 = 100;
    spacingBullet = 0;
    phase = 1;
    mod = 1;
    modX = 1;
    decal = 100;
    metronome = 0;
    std::cout << "__________FIN CONSTRUCTEUR Luna___________" << std::endl;
}

Luna::~Luna()
{
    //UnloadTexture(sprite);
}

void Luna::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *>Luna::Movement_handler(std::vector<iEntity *>)
{
    std::cout << "\t\t\t_____Luna movement_____" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::vector<iEntity *> ret;
    if (metronome == 0 && struc.pos_y != 300) {
        if (struc.pos_y > 300) {
            direction_y = 10;
        } else direction_y = -10;
        struc.pos_y -= direction_y;
    }
    else if (metronome == 0 && struc.pos_x != 1600) {
        if (struc.pos_x > 1600) {
            direction_x = -10;
        } else direction_x = 10;
        struc.pos_x += direction_x;
    }
    else {
        if (struc.pos_y == 300 && struc.pos_x == 1600) {
            metronome = 1;
        }
        else if (struc.pos_x == 300 && struc.pos_y == 300) {
            metronome = 2;
        }
        else if (struc.pos_y == 700 && struc.pos_x == 300) {
            metronome = 3;
        }
        else if (struc.pos_x == 1600 && struc.pos_y == 700) {
            metronome = 4;
        }
        switch (metronome)
        {
        case 1:
            struc.pos_x -= 10;
            break;
        case 2:
            struc.pos_y += 10;
            break;
        case 3:
            struc.pos_x += 10;
            break;
        case 4:
            struc.pos_y -= 10;
        default:
            break;
        }
    }
    if (struc.pos_x < 2000) {
        if (count <= 0) {
            std::cout << "COUNT = 0 BULLET" << std::endl;
            s_Entity tmp = {4, 1, 0, 50 ,(struc.pos_y + decal), (struc.pos_x - 10), 0, 2, false};
            Bullet *bullet = new Bullet(tmp, false);
            ret.push_back(bullet);
            decal -= 10;
            count--;
            if (count == -10) {
                decal = 100;
                int rand = std::rand() % 40;
                count = 20 + rand;
            }
        }
        else {
            count--;
        }
    }
    return (ret);
}

iEntity *Luna::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "______________Luna COLLISION SYS_____________" << std::endl;
    for (int i = 0; i < ids.size(); i++) {
        std::cout << "I = " << i << std::endl;
        for (int j = 0; j < ids.at(i).size(); j++) {
            std::cout << "j = " << j << std::endl;
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            std::cout << "j after if 2 = " << j << std::endl;
            for (int l = 0; l < ram.size(); l++) {
                std::cout << "l = " << l << std::endl;
                if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                    if (ram.at(l)->struc.type == 4) {
                        if (static_cast<Bullet *>(ram.at(l))->isAllied == true) {
                            std::cout << "Luna collides with bullet" << std::endl;
                            this->struc.health -= 15 * ram.at(l)->getStruc()->damage;
                        }
                    }
                }
                std::cout << "APRES COLLISION Luna" << std::endl;
            }
        }
    }
    return (NULL);
}

void Luna::Frame_handler()
{
    std::cout << "__________________FRAME Luna HANDLER__________________" << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
    if (phase == 1) {
        struc.frame += this->mod;
        if (struc.frame >= 1 || struc.frame <= 0) {
            this->mod *= -1;
        }
    }
    else {
        struc.frame = 2;
    }
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME Luna HANDLER____________" << std::endl;
}

s_Entity *Luna::getStruc()
{
    return (&struc);
}

BigSnake::BigSnake(std::vector<s_Entity> entity)
{
    struc.type = entity.at(0).type;
    struc.underType = entity.at(0).underType;
    struc.id = entity.at(0).id;
    struc.health = entity.at(0).health;
    struc.pos_y = entity.at(0).pos_y;
    struc.pos_x = entity.at(0).pos_x;
    struc.frame = entity.at(0).frame;
    struc.damage = entity.at(0).damage;
    std::cout << "Composed type = " << struc.type << std::endl;
    std::cout << "Composed underType = " << struc.underType << std::endl;
    direction_x = -10;
    direction_y = 10;
    max_frame = 1;
    count = 60;
    std::cout << "__________LOOP___________" << std::endl;
    for(int i = 1; i < entity.size(); i++) {
        std::cout << i << std::endl;
        PARTS.push_back(entity.at(i));
    }
    mod = 1;
    std::cout << "__________FIN CONSTRUCTEUR COMPOSED___________" << std::endl;
}

BigSnake::~BigSnake()
{
    //UnloadTexture(sprite);
}

void BigSnake::get_update(s_Entity entity)
{
    struc.pos_y = entity.pos_y;
    struc.pos_x = entity.pos_x;
    struc.health = entity.health;
    struc.damage = entity.damage;
    struc.frame = entity.frame;
}

std::vector<iEntity *> BigSnake::Movement_handler(std::vector<iEntity *>)
{
    std::cout << "\t\t\t_____BigSnake movement_____" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    int exPos_x = 0;
    int exPos_y = 0;
    int exPos_x2 = 0;
    int exPos_y2 = 0;
    if (struc.pos_x == (1920 - (180 * (PARTS.size() + 1)))) {
        direction_x = -10;
    }
    if (struc.pos_x == 0) {
        direction_x = 10;
    }
    struc.pos_x += direction_x;
    exPos_x = struc.pos_x + 180;
    exPos_y = struc.pos_y;
    for (int i = 0; i < PARTS.size() ; i++) {
        exPos_x2 = PARTS.at(i).pos_x + 180;
        PARTS.at(i).pos_x = exPos_x;
        exPos_x = exPos_x2;
        exPos_y2 = PARTS.at(i).pos_y;
        PARTS.at(i).pos_y =  exPos_y;
        exPos_y = exPos_y2;
    }    
    if ((struc.pos_y + 180) >= 1080) {
        direction_y = -10;
    }
    if (struc.pos_y <= 0) {
        direction_y = 10;
    }
    struc.pos_y += direction_y;
    /*PARTS.at(0).pos_x = struc.pos_x + width;
    PARTS.at(0).pos_y = struc.pos_y + height;
    if (struc.pos_x == 1920) {
        direction_x = -10;
    }
    if (struc.pos_x == 0) {
        direction_x = 10;
    }
    if (count == 0) {
        direction_y *= -1;
        count = 20;
    } else count--;
    struc.pos_x += direction_x;
    if (struc.pos_y > 0 && struc.pos_y < 1080)
        struc.pos_y += direction_y;
    std::cout << "\t\t\t___________" << std::endl;
    std::cout << "\t\t\tX = " << struc.pos_x << "&& Y = " << struc.pos_y << std::endl;
    std::cout << "\t\t\t___fin BigSnake movement___" << std::endl;*/
/*     for (int i = this->PARTS.size() - 1; i > 1 ; i--) {
        PARTS.at(i).pos_x = PARTS.at(i - 1).pos_x + width;
        PARTS.at(i).pos_y = PARTS.at(i - 1).pos_y;
    }
    PARTS.at(0).pos_x = struc.pos_x + width;
    PARTS.at(0).pos_y = struc.pos_y + height;
    if (struc.pos_x == 1920) {
        direction_x = -10;
    }
    if (struc.pos_x == 0) {
        direction_x = 10;
    }
    struc.pos_x += direction_x;
    //if (struc.pos_y > 0 && struc.pos_y < 1080)
     //   struc.pos_y += direction_y; */
    return (static_cast<std::vector<iEntity *>>(NULL));
}

iEntity *BigSnake::Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator)
{
    std::cout << "______________BigSnake COLLISION SYS_____________" << std::endl;
    for (int i = 0; i < ids.size(); i++) {
        std::cout << "I = " << i << std::endl;
        for (int j = 0; j < ids.at(i).size(); j++) {
            std::cout << "j = " << j << std::endl;
            if (ids.at(i).at(j) == this->struc.id) {
                j++;
            }
            if (j >= ids.at(i).size()) {
                j = ids.at(i).size() - 1;
            }
            std::cout << "j after if 2 = " << j << std::endl;
            for (int l = 0; l < ram.size(); l++) {
                std::cout << "l = " << l << std::endl;
                if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                    if (ram.at(l)->struc.type == 4) {
                        if (static_cast<Bullet *>(ram.at(l))->isAllied == true) {
                            std::cout << "BigSnake collides with bullet" << std::endl;
                            this->struc.health -= 15 * ram.at(l)->getStruc()->damage;
                        }
                    }
                }
                std::cout << "APRES COLLISION HEAD" << std::endl;
                for (int k = 0; k < PARTS.size(); k++) {
                    if (ram.at(l)->struc.id == ids.at(i).at(j)) {
                        if (ram.at(l)->struc.type == 4) {
                            if (static_cast<Bullet *>(ram.at(l))->isAllied == true) {
                                std::cout << "BigSnake collides with bullet" << std::endl;
                                this->PARTS.at(k).health -= 15 * ram.at(l)->getStruc()->damage;
                            }
                        }
                    }  
                }
                std::cout << "APRES COLLISION PARTS" << std::endl;
            }
        }
    }
    return (NULL);
}

void BigSnake::Frame_handler()
{
    std::cout << "__________________FRAME BigSnake HANDLER__________________" << std::endl;
    std::cout << "MAXFRAME OF ENTITY:" << max_frame << std::endl;
    getStruc()->frame += mod;
    std::cout << "FRAME OF ENTITY:" << struc.frame << std::endl;
    if (struc.frame >= 2 || struc.frame <= 0) {
        mod *= -1;
    }
    std::cout << "___________________________" << std::endl;
    std::cout << "______________FIN FRAME BigSnake HANDLER____________" << std::endl;
}

s_Entity *BigSnake::getStruc()
{
    return (&struc);
}