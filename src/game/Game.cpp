/*
** EPITECH PROJECT, 2022
** B-CPP-500-MAR-5-1-rtype-theo.garnier
** File description:
** Game.cpp
*/

/**
 * @file Game.cpp
 * @brief Game class
 * @version 0.1
 * @date 2022-10-17
 *
 */


#include "Game.hpp"
#include <raylib.h>

Game::Game(/* args */)
{
}

Game::~Game()
{
}

int Game::gameLoop()
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    int isHitted = 0;

    InitWindow(screenWidth, screenHeight, "background of the game");

    Texture2D starship = LoadTexture("assets/sprites/starship.png");

    Texture2D ennemy = LoadTexture("assets/sprites/ennemy.png");

    Vector2 ennemyPosition = {1500, 600};

    Vector2 starshipPosition = {0, 90};

    Texture background = LoadTexture("assets/sprites/Background.png");

    Vector2 offset = { 0,0 };

    fire *bullet = new fire("assets/sprites/bulletv1.png", {starshipPosition.x, starshipPosition.y}, true);

    SetTargetFPS(60);


        offset.x += GetFrameTime() * 50;

        BeginDrawing();

        ClearBackground(WHITE);

        DrawTexturePro(background
                ,(Rectangle) { offset.x, offset.y, GetScreenWidth(), GetScreenHeight() }
                ,(Rectangle) {  0, 0, GetScreenWidth(), GetScreenHeight() }
                ,(Vector2) { 0, 0 }
                , 0
                , WHITE);

        ennemyPosition.x -= GetFrameTime() * 100;

        if (bullet->bulletActive)
        {
            bullet->bulletPos.x += GetFrameTime() * 1000;

            if (bullet->bulletPos.x > starshipPosition.x + 400)
                bullet->bulletActive = false;
        }
        else if (IsKeyDown(KEY_SPACE))
        {
            bullet->bulletActive = true;
            bullet->bulletPos = (Vector2){ starshipPosition.x, starshipPosition.y };
        }

        if (IsKeyDown(KEY_RIGHT)) starshipPosition.x += 10;
        if (IsKeyDown(KEY_LEFT)) starshipPosition.x -= 10;
        if (IsKeyDown(KEY_UP)) starshipPosition.y -= 10;
        if (IsKeyDown(KEY_DOWN)) starshipPosition.y += 10;
        if (IsKeyDown(KEY_D)) starshipPosition.x += 10;
        if (IsKeyDown(KEY_Q)) starshipPosition.x -= 10;
        if (IsKeyDown(KEY_Z)) starshipPosition.y -= 10;
        if (IsKeyDown(KEY_S)) starshipPosition.y += 10;


        if (starshipPosition.x >= 1830)
            starshipPosition.x = 1830;
        if (starshipPosition.x <= 0)
            starshipPosition.x = 0;
        if (starshipPosition.y >= 990)
            starshipPosition.y = 990;
        if (starshipPosition.y <= 0)
            starshipPosition.y = 0;

        if (bullet->bulletPos.x >= ennemyPosition.x && bullet->bulletPos.x >= ennemyPosition.x && bullet->bulletPos.y == bullet->bulletPos.y)
            isHitted = 1;

        DrawTexture(starship, starshipPosition.x, starshipPosition.y, WHITE);

        if (bullet->bulletActive)
            DrawTexture(bullet->bullet, bullet->bulletPos.x, bullet->bulletPos.y, WHITE);

        if (ennemyPosition.x > 0 && isHitted != 1)
            DrawTexture(ennemy, ennemyPosition.x, ennemyPosition.y, WHITE);

        EndDrawing();

    CloseWindow();

    return 0;
}