/*
** EPITECH PROJECT, 2022
** TEK3
** File description:
** Entity
*/

/**
 * @file Entity.hpp
 * @brief Entity class
 * @version 0.1
 * @date 2022-10-17
 *
 */

#include <vector>
#include <iostream>
#include "Macro.hpp"
#include "raylib.h"

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

struct s_Entity
{
    int type;
    int underType;
    int id;
    int health;
    int pos_y; // modif par 
    int pos_x;
    int frame;         // get_update()
    int damage;   // if (On_screen == false)  {
    int i_frame;      // display.at(..).~destructor
    bool hasPLayed;   // display.erase
                       // while (cache id != id_to_erase)
                       // } ... souvenir de lindex puis erase du cache
};

class iEntity {
    public:
        virtual ~iEntity() = default;
        //SETTERS//
        virtual void get_update(s_Entity) = 0;
        //GETTERS//
        virtual s_Entity *getStruc() = 0;
        virtual std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram) = 0;
        virtual iEntity *Collision_handler(std::vector<std::vector<int>>, std::vector<iEntity *>, int *id_generator) = 0;
        virtual void Frame_handler() = 0;
        //virtual std::vector<std::vector<std::vector<s_Entity>>> Collision_handler(s_Entity Target, std::vector<s_Entity> RAMMED_DATABASE) = 0;
        s_Entity struc;
        int max_frame;
        int width;
        int height;
        int mod;
        //DATAS//
/*         int type;
        int id;
        int health;
        std::vector<float> position;
        Texture2D sprite;
        int frame;
        int damage;
        bool on_screen; */
    protected:
    private:
};

class Player : public iEntity {
    public:
        Player(s_Entity);
        ~Player();
        //SETTERS//
        void get_update(s_Entity);
        //GETTERS//
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        iEntity *Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator);
        void Frame_handler();
        //std::vector<std::vector<std::vector<s_Entity>>> Collision_handler(s_Entity Target, std::vector<s_Entity> RAMMED_DATABASE);
        int bonus;
        int weapon;
        int maxCount;
        int count;
        int bouncingBullet;
        bool isDead;
        //DATAS//
        /* int type;
        int id;
        int health;
        std::vector<float> position;
        Texture2D sprite;
        int frame;
        int damage;
        bool on_screen; */
    protected:
    private:
};

class Enemy : public iEntity {
    public:
        Enemy(s_Entity);
        ~Enemy();
        //SETTERS//
        void get_update(s_Entity);
        //GETTERS//
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        iEntity *Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator);
        void Frame_handler();
        //std::vector<std::vector<std::vector<s_Entity>>> Collision_handler(s_Entity Target, std::vector<s_Entity> RAMMED_DATABASE);
        //DATAS//
        /* int type;
        int id;
        int health;
        std::vector<float> position;
        Texture2D sprite;
        int frame;
        int damage;
        bool on_screen; */
    protected:
    private:
};

class ShootingEnemy : public iEntity {
    public:
        ShootingEnemy(s_Entity);
        ~ShootingEnemy();
        //SETTERS//
        void get_update(s_Entity);
        //GETTERS//
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        iEntity *Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator);
        void Frame_handler();
        int count;
        //std::vector<std::vector<std::vector<s_Entity>>> Collision_handler(s_Entity Target, std::vector<s_Entity> RAMMED_DATABASE);
        //DATAS//
        /* int type;
        int id;
        int health;
        std::vector<float> position;
        Texture2D sprite;
        int frame;
        int damage;
        bool on_screen; */
    protected:
    private:
};

class ComposedEnemy : public iEntity {
    public:
        ComposedEnemy(std::vector<s_Entity>);
        ~ComposedEnemy();
        //SETTERS//
        void get_update(s_Entity);
        //GETTERS//
        void Frame_handler();
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        std::vector<s_Entity> PARTS;
        iEntity *Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator);
        int direction_x;
        int direction_y;
        int count;
};

class Boss : public iEntity {
    public:
        Boss(std::vector<s_Entity>);
        ~Boss();
        void get_update(s_Entity);
        //GETTERS//
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        void Frame_handler();
        void PHASE_1();
        void PHASE_2();
        void PHASE_3();
        std::vector<s_Entity> PARTS;
        iEntity *Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator);
        int direction_x;
        int direction_y;
        int direction_ypart1;
        int direction_ypart2;
        int count;
        int countCanon1;
        int countCanon2;
        int countShooting1;
        int countShooting2;
        int countPhase2;
        int spacingBullet;
        int phase;
};


class Dummy : public iEntity {
    public:
        Dummy(s_Entity);
        ~Dummy();
        void get_update(s_Entity);
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        iEntity *Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator);
        void Frame_handler();
        bool isEntity;
};

class Bonus : public iEntity {
    public:
        Bonus(s_Entity);
        ~Bonus();
        void get_update(s_Entity);
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        iEntity *Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator);
        void Frame_handler();
};

class Bullet : public iEntity {
    public:
        Bullet(s_Entity, bool);
        ~Bullet();
        //SETTERS//
        void get_update(s_Entity);
        //GETTERS//
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        iEntity *Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator);
        void Frame_handler();
        bool isAllied;
        //std::vector<std::vector<std::vector<s_Entity>>> Collision_handler(s_Entity Target, std::vector<s_Entity> RAMMED_DATABASE); 
        //DATAS//
        /* int type;
        int id;
        int health;
        std::vector<float> position;
        Texture2D sprite;
        int frame;
        int damage;
        bool on_screen; */
    protected:
    private:
};

class Laser : public iEntity {
    public:
        Laser(s_Entity, bool);
        ~Laser();
        //SETTERS//
        void get_update(s_Entity);
        //GETTERS//
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        iEntity *Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator);
        void Frame_handler();
        bool isAllied;
        int count;
        //std::vector<std::vector<std::vector<s_Entity>>> Collision_handler(s_Entity Target, std::vector<s_Entity> RAMMED_DATABASE); 
        //DATAS//
        /* int type;
        int id;
        int health;
        std::vector<float> position;
        Texture2D sprite;
        int frame;
        int damage;
        bool on_screen; */
    protected:
};

class Bloc : public iEntity {
    public:
        Bloc(s_Entity);
        ~Bloc();
        //SETTERS//
        void get_update(s_Entity);
        //GETTERS//
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        iEntity *Collision_handler(std::vector<std::vector<int>>, std::vector<iEntity *>, int *id_generator);
        void Frame_handler();
        //std::vector<std::vector<std::vector<s_Entity>>> Collision_handler(s_Entity Target, std::vector<s_Entity> RAMMED_DATABASE);
        //DATAS//
        /* int type;
        int id;
        int health;
        std::vector<float> position;
        Texture2D sprite;
        int frame;
        int damage;
        bool on_screen; */
    protected:
    private:
};

class Weapon : public iEntity {
    public:
        Weapon(s_Entity);
        ~Weapon();
        void get_update(s_Entity);
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        iEntity *Collision_handler(std::vector<std::vector<int>>, std::vector<iEntity *>, int *id_generator);
        void Frame_handler();
};

class Rocket : public iEntity {
    public:
        Rocket(s_Entity, bool);
        ~Rocket();
        //SETTERS//
        void get_update(s_Entity);
        //GETTERS//
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        iEntity *Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator);
        void Frame_handler();
        bool isAllied;
        //std::vector<std::vector<std::vector<s_Entity>>> Collision_handler(s_Entity Target, std::vector<s_Entity> RAMMED_DATABASE); 
        //DATAS//
        /* int type;
        int id;
        int health;
        std::vector<float> position;
        Texture2D sprite;
        int frame;
        int damage;
        bool on_screen; */
    protected:
    private:
};

class BouncingBullet : public Bullet {
    public:
        BouncingBullet(s_Entity entity, bool b, int modX, int modY, int dirX, int dirY);
        ~BouncingBullet();
        //SETTERS//
        void get_update(s_Entity);
        //GETTERS//
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        iEntity *Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator);
        void Frame_handler();
        int modX;
        int modY;
        int directionX;
        int directionY;
        int rebond;
        //std::vector<std::vector<std::vector<s_Entity>>> Collision_handler(s_Entity Target, std::vector<s_Entity> RAMMED_DATABASE); 
        //DATAS//
        /* int type;
        int id;
        int health;
        std::vector<float> position;
        Texture2D sprite;
        int frame;
        int damage;
        bool on_screen; */
    protected:
    private:
};

class Sol : public iEntity {
    public:
        Sol(s_Entity);
        ~Sol();
        //SETTERS//
        void get_update(s_Entity);
        //GETTERS//
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        iEntity *Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator);
        void Frame_handler();
        int direction_x;
        int direction_y;
        int count;
        int modX;
        int countCanon1;
        int countShooting1;
        int countPhase2;
        int spacingBullet;
        int phase;
        int decal;
        int metronome;
        bool lunaSpawn;
    protected:
    private:
};

class Luna : public iEntity {
    public:
        Luna(s_Entity);
        ~Luna();
        //SETTERS//
        void get_update(s_Entity);
        //GETTERS//
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        iEntity *Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator);
        void Frame_handler();
        int direction_x;
        int direction_y;
        int count;
        int modX;
        int countCanon1;
        int countShooting1;
        int countPhase2;
        int spacingBullet;
        int phase;
        int decal;
        int metronome;
    protected:
    private:
};

class BigSnake : public iEntity {
    public:
        BigSnake(std::vector<s_Entity>);
        ~BigSnake();
        //SETTERS//
        void get_update(s_Entity);
        //GETTERS//
        void Frame_handler();
        s_Entity *getStruc();
        std::vector<iEntity *> Movement_handler(std::vector<iEntity *> ram);
        std::vector<s_Entity> PARTS;
        iEntity *Collision_handler(std::vector<std::vector<int>> ids, std::vector<iEntity *> ram, int *id_generator);
        int direction_x;
        int direction_y;
        int count;
};


#endif /* !ENTITY_HPP_ */