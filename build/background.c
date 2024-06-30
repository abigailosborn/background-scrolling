#include "raylib.h"

int main(void){
    const int screenwidth = 700;
    const int screenheight = 400;
    const float velocity = 2.0f;
    
    float posX = 50;
    float posY = 283;

    InitWindow(screenwidth, screenheight, "Background Scrolling");
    
    Texture2D background = LoadTexture("bg1.png");
    Texture2D midground = LoadTexture("bg2.png");
    Texture2D foreground = LoadTexture("bg3.png");
    Texture2D player = LoadTexture("cow.png");

    float scrolling_back = 0.0f;
    float scrolling_mid = 0.0f;
    float scrolling_fore = 0.0f;

    SetTargetFPS(60);

    while(!WindowShouldClose()){

        if(IsKeyDown(KEY_RIGHT)){
            scrolling_back -= 0.1f;
            scrolling_mid -= 0.5f;
            scrolling_fore -= 2.0f;

            if(scrolling_back <= -background.width*2) scrolling_back = 0;
            if(scrolling_mid <= -midground.width*2) scrolling_mid = 0;
            if(scrolling_fore <= -foreground.width*2) scrolling_fore = 0;
            

             posX += velocity;
        }

        if(IsKeyDown(KEY_LEFT)){
             posX -= velocity;  

             scrolling_back += 0.1f;
             scrolling_mid += 0.5f;
             scrolling_fore += 2.0f;

             if(scrolling_back >= background.width*2) scrolling_back = 0;
             if(scrolling_mid >= midground.width*2) scrolling_mid = 0;
             if(scrolling_fore >= foreground.width*2) scrolling_fore = 0;
                     
        }

        BeginDrawing();

            ClearBackground(GetColor(0x052c46ff));

            DrawTextureEx(background, (Vector2){ scrolling_back, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrolling_back, 20 }, 0.0f, 2.0f, WHITE);

            DrawTextureEx(midground, (Vector2){ scrolling_mid, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(midground, (Vector2){ midground.width*2 + scrolling_mid, 20 }, 0.0f, 2.0f, WHITE);

            DrawTextureEx(foreground, (Vector2){scrolling_fore, 70}, 0.0f, 2.0f, WHITE);
            DrawTextureEx(foreground, (Vector2){foreground.width*2 + scrolling_fore, 70}, 0.0f, 2.0f, WHITE);

            DrawTexture(player, posX, posY, WHITE);
        EndDrawing();
    }
    
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);

    CloseWindow();
    return 0;
}
