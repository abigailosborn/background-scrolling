#include <stdio.h>
#include "raylib.h"

#define GRAVITY 3.0f
#define PLAYER_JUMP_SPEED 10.0f
#define PLAYER_HOR_SPEED 60.0f

bool left_col = false;
bool right_col = false;
bool top_col = false;
bool bottom_col = false;

Rectangle collision_box = {0};

//Set characteristics for the player
typedef struct Player{
    float velocity;
    Vector2 position;
    float speed;
    float width;
    float height;
    bool can_jump;
    bool can_move_left;
    bool can_move_right;
}Player;

//Set characteristics for environment objects
typedef struct EnvItem{
    Rectangle rect;
    int blocking;
    Color color; 
} EnvItem;

void ResetCollision(bool *left_col, bool *right_col, bool *top_col, bool *bottom_col){
    left_col = false;
    right_col = false;
    top_col = false;
    bottom_col = false;
}
void CheckCollisionSide(Player *player, EnvItem *env_items, int env_items_length){
    //Player collision
    bool collision = false;
    Rectangle player_rec = {player->position.x, player->position.y, player->height, player->width};
    for(int i = 0; i < env_items_length; i++){
        EnvItem obstacle = env_items[i];
        collision = CheckCollisionRecs(obstacle.rect, player_rec);
        collision_box = GetCollisionRec(obstacle.rect, player_rec);
       
        if(player->position.x <= obstacle.rect.x + obstacle.rect.width && player->position.x > obstacle.rect.x){
            if(player->position.y + player->height < obstacle.rect.y && player->position.y < obstacle.rect.y + obstacle.rect.height){
            //left
                left_col = true;
            }
        }
        if(player->position.x + player->width >= obstacle.rect.x && player->position.x + player->width <= obstacle.rect.x + obstacle.rect.width){
            //right
            if(player->position.y + player->height < obstacle.rect.y && player->position.y < obstacle.rect.y + obstacle.rect.height){
                right_col = true;;
//            }
        }
        if(obstacle.rect.y <= player->position.y + player->height && player->position.y + player->height <= obstacle.rect.y + obstacle.rect.height){
            //if(player->position.x + player->width < obstacle.rect.x && player->position.y < obstacle.rect.x + obstacle.rect.height){
                //bottom
                bottom_col = true;
            }
        }
        ResetCollision(&left_col, &right_col, &top_col, &bottom_col);
    }
}

//Function Declarations
void UpdatePlayer(Player *player, EnvItem *env_items, int env_items_length, float delta);


//Player movement and collision
void UpdatePlayer(Player *player, EnvItem *env_items, int env_items_length, float delta){
    //Check if this is doing anything
    DrawText("HI", GetScreenWidth()/2 - MeasureText("HI", 20), 100, 100, BLACK);
    //Define player Rectangle
    Rectangle player_rec = {player->position.x, player->position.y, 20.0f, 20.0f};
    //Player movement
    if(IsKeyDown(KEY_LEFT) && player->can_move_left){
        player->position.x -= PLAYER_HOR_SPEED*delta;
        DrawText("LEFT", GetScreenWidth()/2 - MeasureText("LEFT", 20), 100, 100, BLACK);
    }
    if(IsKeyDown(KEY_RIGHT) && player->can_move_right){
        player->position.x += PLAYER_HOR_SPEED*delta;
    }
    if(IsKeyDown(KEY_SPACE) && player->can_jump){
        player->velocity = 6.0f; 
        player->position.y -= player->velocity;
        player->can_jump = false;

    }
    if(!player->can_jump){
        player->velocity -= .2;
    }
    //Player collision
    bool collision = false;
    int collision_position = 0;

    for(int i = 0; i < env_items_length; i++){
        EnvItem obstacle = env_items[i];
        collision = CheckCollisionRecs(obstacle.rect, player_rec);
        if(!collision){
            player->can_jump = false;
        }
        else{
            CheckCollisionSide(player, env_items, env_items_length);
            collision_box = GetCollisionRec(obstacle.rect, player_rec);
            printf("%d", collision_position);
            player->can_jump = true;
       }
    }
    if(bottom_col == false){
        player->position.y += GRAVITY;
    }
    if(left_col == true){

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
    player.velocity = 4.0;
    player.can_jump = false;
    player.width = 20.0f;
    player.height = 20.0f;
    player.can_move_left = true;
    player.can_move_right = true;

    //Set up environment items
    EnvItem env_items[] = {
        {{0, 400, 800, 50}, 1, GREEN},
        {{0, 200, 40, 200}, 1, GREEN},
        {{400, 200, 40, 200}, 1, GREEN}
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
            DrawRectangle(player.position.x, player.position.y, player.width, player.height, BLUE);
            DrawRectangleRec(collision_box, RED);
        EndDrawing();
    } 

    CloseWindow();

    return 0;
}
