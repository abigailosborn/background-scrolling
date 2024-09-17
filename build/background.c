#include "raylib.h"

int main(void){
    const int screenwidth = 700;
    const int screenheight = 400;
    const float velocity = 1.0f;
    
    bool is_moving = false;
    bool is_jumping = false;
    bool on_ground = false;
        
    float posX = 50;
    float posY = 250;

    InitWindow(screenwidth, screenheight, "Background Scrolling");
    
    Texture2D background = LoadTexture("bg1.png");
    Texture2D midground = LoadTexture("bg2.png");
    Texture2D ground = LoadTexture("bg3.png");
    Texture2D player = LoadTexture("cow_sprite_sheet.png");
    Texture2D still_player = LoadTexture("cow.png");
    
    Rectangle still = {0.0f, 0.0f, (float)still_player.width, (float)still_player.height};
    Rectangle frame_rec = {0.0f, 0.0f, (float)player.width/4, (float)player.height};
    
    Rectangle floor = {0.0f, 0.0f, (float)ground.width, (float)ground.height};

    int current_frame = 0;
    int frames_counter = 0;
    int frame_speed = 6;

    float scrolling_back = 0.0f;
    float scrolling_mid = 0.0f;
    //float scrolling_fore = 0.0f;

    SetTargetFPS(60);

    while(!WindowShouldClose()){

        //track frames for sprite animation
        frames_counter++;
        
        if(frames_counter >= (60/frame_speed)){
            frames_counter = 0;
            current_frame++;

            if(current_frame > 3) current_frame = 0;
            frame_rec.x = (float)current_frame*(float)player.width/4;
        }
    

        //choose what animations to use for each sprite and make the background scroll
        if(IsKeyDown(KEY_RIGHT)){
            scrolling_back -= 0.1f;
            scrolling_mid -= 0.5f;
            //scrolling_fore -= 2.0f;

            if(scrolling_back <= -background.width*2) scrolling_back = 0;
            if(scrolling_mid <= -midground.width*2) scrolling_mid = 0;
            //if(scrolling_fore <= -foreground.width*2) scrolling_fore = 0;
            
            is_moving = true;

            posX += velocity;
        }
        else if(IsKeyDown(KEY_LEFT)){
             posX -= velocity;  

             scrolling_back += 0.1f;
             scrolling_mid += 0.5f;
             //scrolling_fore += 2.0f;

             if(scrolling_back >= background.width*2) scrolling_back = 0;
             if(scrolling_mid >= midground.width*2) scrolling_mid = 0;
             //if(scrolling_fore >= foreground.width*2) scrolling_fore = 0;
             
             is_moving = true;        
        }
        else if(IsKeyDown(KEY_SPACE)){
            posY -= velocity;
            is_jumping = true;
        }
        else{
            is_moving = false;
            is_jumping = false;
        }

        //gravity? I hate Gravity
        on_ground = CheckCollisionRecs(frame_rec, floor);       
        //For some reason cow is being read as always colliding with the ground
        if(!on_ground){
            posY += velocity;
        } 

        BeginDrawing();

            ClearBackground(GetColor(0x052c46ff));

            DrawTextureEx(background, (Vector2){ scrolling_back, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrolling_back, 20 }, 0.0f, 2.0f, WHITE);

            DrawTextureEx(midground, (Vector2){ scrolling_mid, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(midground, (Vector2){ midground.width*2 + scrolling_mid, 20 }, 0.0f, 2.0f, WHITE);

            //DrawTextureEx(foreground, (Vector2){scrolling_fore, 70}, 0.0f, 2.0f, WHITE);
            //DrawTextureEx(foreground, (Vector2){foreground.width*2 + scrolling_fore, 70}, 0.0f, 2.0f, WHITE);
            
            DrawTextureRec(ground, floor, (Vector2){0, 375}, WHITE);


            if(is_moving){
                DrawTextureRec(player, frame_rec, (Vector2){posX, posY}, WHITE);
            }
            else{
                DrawTextureRec(still_player, still, (Vector2){posX, posY}, WHITE);
            }

            //Debug collision issues
            if(on_ground){
                DrawText("COLLISION", GetScreenWidth()/2 - MeasureText("COLLISION", 20)/2, GetScreenHeight()/2 -10, 20, BLACK); 
            }
        EndDrawing();
    }
    
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(ground);
    UnloadTexture(player);

    CloseWindow();
    return 0;
}
