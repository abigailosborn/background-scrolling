#include "raylib.h"

int main(void){
    const int screenwidth = 700;
    const int screenheight = 400;
    const float velocity = 2.0f;
    
    bool is_moving = false;
        
    float posX = 50;
    float posY = 283;

    InitWindow(screenwidth, screenheight, "Background Scrolling");
    
    Texture2D background = LoadTexture("bg1.png");
    Texture2D midground = LoadTexture("bg2.png");
    Texture2D foreground = LoadTexture("bg3.png");
    Texture2D player = LoadTexture("cow_sprite_sheet.png");
    Texture2D still_player = LoadTexture("cow.png");
    
    Rectangle still = {0.0f, 0.0f, (float)still_player.width, (float)still_player.height};
    Rectangle frame_rec = {0.0f, 0.0f, (float)player.width/4, (float)player.height};
    
    int current_frame = 0;
    int frames_counter = 0;
    int frame_speed = 8;

    float scrolling_back = 0.0f;
    float scrolling_mid = 0.0f;
    float scrolling_fore = 0.0f;

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
    

        if(IsKeyDown(KEY_RIGHT)){
            scrolling_back -= 0.1f;
            scrolling_mid -= 0.5f;
            scrolling_fore -= 2.0f;

            if(scrolling_back <= -background.width*2) scrolling_back = 0;
            if(scrolling_mid <= -midground.width*2) scrolling_mid = 0;
            if(scrolling_fore <= -foreground.width*2) scrolling_fore = 0;
            
            is_moving = true;

            posX += velocity;
        }
        else if(IsKeyDown(KEY_LEFT)){
             posX -= velocity;  

             scrolling_back += 0.1f;
             scrolling_mid += 0.5f;
             scrolling_fore += 2.0f;

             if(scrolling_back >= background.width*2) scrolling_back = 0;
             if(scrolling_mid >= midground.width*2) scrolling_mid = 0;
             if(scrolling_fore >= foreground.width*2) scrolling_fore = 0;
             
             is_moving = true;        
        }
        else{
            is_moving = false;
        }

        BeginDrawing();

            ClearBackground(GetColor(0x052c46ff));

            DrawTextureEx(background, (Vector2){ scrolling_back, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrolling_back, 20 }, 0.0f, 2.0f, WHITE);

            DrawTextureEx(midground, (Vector2){ scrolling_mid, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(midground, (Vector2){ midground.width*2 + scrolling_mid, 20 }, 0.0f, 2.0f, WHITE);

            DrawTextureEx(foreground, (Vector2){scrolling_fore, 70}, 0.0f, 2.0f, WHITE);
            DrawTextureEx(foreground, (Vector2){foreground.width*2 + scrolling_fore, 70}, 0.0f, 2.0f, WHITE);

            if(is_moving){
                DrawTextureRec(player, frame_rec, (Vector2){posX, posY}, WHITE);
            }
            else{
                DrawTextureRec(still_player, still, (Vector2){posX, posY}, WHITE);
            }
        EndDrawing();
    }
    
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    UnloadTexture(player);

    CloseWindow();
    return 0;
}
