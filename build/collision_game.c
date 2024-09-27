#include <stdio.h>
#include "raylib.h"

#define GRAVITY 6.0f
#define PLAYER_JUMP_SPEED 10.0f
#define PLAYER_HOR_SPEED 60.0f

Rectangle collision_box = {0};

//Set characteristics for the player
typedef struct Player{
    Vector2 position;
    float speed;
    bool can_jump;
}Player;

//Set characteristics for environment objects
typedef struct EnvItem{
    Rectangle rect;
    int blocking;
    Color color; 
} EnvItem;

//Function Declarations
void UpdatePlayer(Player *player, EnvItem *env_items, int env_items_length, float delta);


//Player movement and collision
void UpdatePlayer(Player *player, EnvItem *env_items, int env_items_length, float delta){
    //Check if this is doing anything
    DrawText("HI", GetScreenWidth()/2 - MeasureText("HI", 20), 100, 100, BLACK);
    //Define player Rectangle
    Rectangle player_rec = {player->position.x, player->position.y, 20.0f, 20.0f};
    //Player movement
    if(IsKeyDown(KEY_LEFT)){
        player->position.x -= PLAYER_HOR_SPEED*delta;
        DrawText("LEFT", GetScreenWidth()/2 - MeasureText("LEFT", 20), 100, 100, BLACK);
    }
    if(IsKeyDown(KEY_RIGHT)){
        player->position.x += PLAYER_HOR_SPEED*delta;
    }
    if(IsKeyDown(KEY_SPACE) && player->can_jump){
        player->position.y -= PLAYER_JUMP_SPEED;
        player->can_jump = false;
    }
    //Player collision
    bool collision = false;
    for(int i = 0; i < env_items_length; i++){
        EnvItem obstacle = env_items[i];
        collision = CheckCollisionRecs(obstacle.rect, player_rec);
        if(!collision){
            player->can_jump = false;
            player->position.y += GRAVITY;
        }
        else{
            collision_box = GetCollisionRec(obstacle.rect, player_rec);
            player->can_jump = true;
            //check if reading collision
            DrawText("COLLISION!", GetScreenWidth()/2 - MeasureText("COLLISION!", 20)/2, 50, 50, RED);
            break;
        }
    }
        
} 

int main(void){
    //Set screen parameters
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    //define the player character
    Player player = {0};
    player.position = (Vector2){20.0f, 20.0f};
    player.speed = 0;
    player.can_jump = false;

    //Set up environment items
    EnvItem env_items[] = {
        {{0, 400, 800, 50}, 1, GREEN}
    };

    //Find the amount of environment items
    int env_items_length = sizeof(env_items)/sizeof(env_items[0]);
    
    InitWindow(screenWidth, screenHeight, "Collision hopefully");

    SetTargetFPS(60);

    while (!WindowShouldClose()){
        
        float delta_time = GetFrameTime(); 
//        UpdatePlayer(&player, env_items, env_items_length, delta_time);

        BeginDrawing();
            UpdatePlayer(&player, env_items, env_items_length, delta_time);  
            ClearBackground(WHITE);
            for(int i = 0; i < env_items_length; i++){
                DrawRectangleRec(env_items[i].rect, env_items[i].color);
            }
            DrawRectangle(player.position.x, player.position.y, 20.0f, 20.0f, BLUE);
            DrawRectangleRec(collision_box, RED);
        EndDrawing();
    } 

    CloseWindow();

    return 0;
}
