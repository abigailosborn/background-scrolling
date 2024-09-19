#include <stdio.h>
#include "raylib.h"

int main(void){
    //Set screen parameters
    const int screenWidth = 800;
    const int screenHeight = 450;

    Vector2 player_position = {20.0f, 20.0f};

    InitWindow(screenWidth, screenHeight, "Collision hopefully");

    Rectangle floor = {0, 400, 800, 50};

    float velocity = 2.0f;
    float jump_velocity = 20.0f;
     
    Rectangle box_collision = {0};

    bool collision = false;

    bool is_jumping = false;

    SetTargetFPS(60);

    while (!WindowShouldClose()){
         
       Rectangle player = {player_position.x, player_position.y, 40, 40};

        if(IsKeyDown(KEY_RIGHT)){
            player_position.x += velocity;
        }            
        if(IsKeyDown(KEY_LEFT)){
            player_position.x -= velocity;
        }
        if(IsKeyDown(KEY_SPACE) && !is_jumping){
            player_position.y -= jump_velocity;
            is_jumping = true;
        }

        collision = CheckCollisionRecs(floor, player);    
        
        if(!collision){
            player_position.y += velocity;
        }
        if(collision){
            box_collision = GetCollisionRec(floor, player);
            is_jumping = false;
        }

        BeginDrawing();
    
            ClearBackground(WHITE);

            DrawRectangleRec(floor, GREEN);
            DrawRectangleRec(player, BLUE);
        
            if(collision){
                DrawRectangleRec(box_collision, RED);
                DrawText("Collision!", 200, 400, 30, BLACK);
            }
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
