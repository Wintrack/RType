/*
** EPITECH PROJECT, 2022
** TEK3
** File description:
** System
*/

#include <vector>
#include "Entity.hpp"
#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_
#include "fire.hpp"

struct Entity_to_display{
    Texture2D texture;
    int id;
};

namespace Systems{
    class MovementSystem {
        public:
            MovementSystem();
            ~MovementSystem();
            std::vector<iEntity *> World_Movement_handler(std::vector<iEntity *> DATABASE, std::vector<s_Entity>, int *id_generator);
            void Movement_AI_On_Screen();
            int lock;
            int alive;
        protected:
        private:
    };

    class CollisionSystem {
        public:
            CollisionSystem();
            ~CollisionSystem();
            std::vector<std::vector<std::vector<s_Entity>>> World_Collision_handler(std::vector<iEntity *> RAMMED_DATABASE);
            std::vector<std::vector<int>> Collision_handler(s_Entity Target, std::vector<s_Entity> *RAMMED_DATABASE);
        protected:
        private:
    };

    class FrameSystem {
        public:
            FrameSystem();
            ~FrameSystem();
            std::vector<iEntity *> World_Frame_handler(std::vector<iEntity *> DATABASE);
        protected:
        private:
            int count;
            int value;
    };

    class CameraSystem { //pour la scénerie 2nd temps
        public:
            CameraSystem();
            ~CameraSystem();
            int Camera_handler();
    };

    class RAM_MEMORY_System { // truc qui gère ce qui est envoyé au cache du jeu, ce qui est à l'écran
        public:
            RAM_MEMORY_System();
            ~RAM_MEMORY_System();
            std::vector<s_Entity> RAM_handler(std::vector<iEntity *> DATABASE);
    };

    class HealthSystem {
        public:
            HealthSystem();
            ~HealthSystem();
            std::vector<s_Entity> World_Health_handler(std::vector<std::vector<std::vector<s_Entity>>>);
            std::vector<s_Entity> Health_handler(std::vector<std::vector<std::vector<s_Entity>>>);
            int health_barre(int health, int pos_x, int pos_y);
        protected:
        private:
    };
    class LivingSystem {
        public:
            LivingSystem();
            ~LivingSystem();
            std::vector<iEntity *> Living_handler(std::vector<iEntity *>, int *id_generator);
        protected:
        private:
    };
    class AudioSystem {
        public:
            AudioSystem();
            ~AudioSystem();
            std::vector<float> Audio_handler(struct s_Entity);
        protected:
        private:
    };
    class RenderingSystem {
        public:
            RenderingSystem();
            ~RenderingSystem();
            INSTRUCTION_GENERIC Rendering_handler(std::vector<s_Entity> displayed, int id);
        protected:
        private:
            int healthset;
            INSTRUCTION_GENERIC SENDED_INFO;
            int screenWidth;
            int screenHeight;
            int isHitted;
            Texture2D starship;
            Texture2D ennemy;
            Texture background;
            Vector2 ennemyPosition;
            Vector2 starshipPosition;
            std::vector<Entity_to_display> Texture_starship;
            std::vector<Entity_to_display> Texture_ennemy;
            std::vector<Entity_to_display> Texture_bg;
            std::vector<Entity_to_display> Texture_bullet;
            std::vector<Entity_to_display> Texture_block;
            fire *bullet;
            Vector2 offset;


            Vector2 _pos_bullet;
            Vector2 _pos_ship;
            Rectangle _frameRecShip;
            Rectangle _freameRecBullet;
    };
}


#endif /* !SYSTEM_HPP_ */
