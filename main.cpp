# include <raylib.h>
#include <stdlib.h>
#include<time.h>
using namespace std;

typedef struct 
{
    int x;
    int y;
    float size;
    float velocity;
}Ball;
typedef struct 
{
    int x;
    int y;
    int height;
    int width;
}Platform;


float rand_float() {

    return (float)((float)rand() / (float ) RAND_MAX);
}


bool paused = false ;

int ball_on_platform( Ball ball, Platform platforms[],int count)
{   

    for (int i = 0; i < count; i++)
    {
       Platform platform = platforms[i];
       Rectangle ball_rec = {.x = ball.x- ball.size +10 ,
                              .y = ball.y + ball.size/2 ,
                              .width = ball.size * 2  ,
                              .height = ball.size 
                              
                            };

        Rectangle platform_rec = { .x = static_cast<float>(platforms[i].x) , 
                                    .y = static_cast<float>(platforms[i].y),
                                    .width = static_cast<float>(platforms[i].width ),
                                    .height = static_cast<float>(platforms[i].height)
                                    
                                    };
                                    
        
        
        if( CheckCollisionRecs(ball_rec,platform_rec) )
        {
          return true;
        }else if (ball.y > 1005)
        {
            return true;
        }
    }
  return false;
    
   
     
};









int main()
{

    srand (time (0));
    int window_heigt = 1080;
    int window_breadth = 1920;

    Color grey = {29,29,27,255};
    SetTargetFPS(60);
    

    Ball ball = {
        .x = window_heigt/2,
        .y = window_breadth/2,
        .size = 40,
        .velocity = 0.2

    };
    Vector2 camera_offset = {
        .x =0,
        .y =0
    };
    Vector2 camera_target = {
        .x =0,
        .y =0
    };
    

    Camera2D camera = {
        .offset = camera_offset,
        .target = camera_target,
        .rotation =0,
        .zoom = 1


    };
    int world_width = window_breadth * 10;
    int platform_width = abs (window_breadth * 0.3) ;
    int platform_count =1000;

    
    Platform platforms [platform_count+ 1];
/*creating floor
    platforms[0].x = 0;
    platforms[0].y = window_heigt - 10;
    platforms[0].width = window_breadth * 10;
    platforms[0].height = 10;*/
// creating more platforms

    int platform_x = abs(window_breadth * 0.1);
    int platform_max_y = abs(window_heigt* 0.7);
    int platform_min_y =abs(window_heigt* 0.1);

    for (int  i = 1; i <= platform_count; i++)
    {
        int random_number = rand_float () * platform_max_y;


        platforms[i].x =   platform_x ;
        platforms[i].y =  abs (random_number  )+ platform_min_y ;
        platforms[i].width =abs(window_breadth * 0.05);
        platforms[i].height = abs(window_heigt * 0.5);

        platform_x += platforms[i].width + abs(window_breadth * 0.2);
    }

    

    //int platform_count = sizeof(platforms)/ sizeof(Platform);

    InitWindow(window_breadth,window_heigt,"Bounce");
    

    while (WindowShouldClose() == false)
    {
    BeginDrawing();
    BeginMode2D(camera);

    if (ball.x > window_breadth *0.8)
    {
        camera.offset.x = -(ball.x -window_breadth *0.5);
    } else if (ball.x < window_breadth *0.2)
    {
       camera.offset.x = -(ball.x -window_breadth *0.5);
    }
    if (camera.offset.x > 0)
    {
        camera.offset.x = 0 ;

    }
    
    if(!paused)
     {   
    ball.x +=3;
    ball.y += ball.velocity;
    ball.velocity += 0.3;
    DrawCircle(ball.x,ball.y,ball.size,GREEN);
   
     }
        int ball_hits= ball_on_platform(ball,platforms ,platform_count );
    if (ball_hits == true)
    {
        
        ball.x = 0;
        ball.y = 0;
        ball.velocity=0;



    }

    if(IsKeyPressed(KEY_P))
    { paused = !paused;}

    if (IsKeyDown(KEY_W))
        {
        ball.velocity = -8;
        }    
    if(IsKeyDown(KEY_A))
    {
         ball.x -=5;
            
    }else if (IsKeyDown(KEY_D))
    {
         ball.x +=5;
    }
        
        
        
    
    ClearBackground(grey);

    for (int i = 0; i < platform_count; i++)  
    {
        DrawRectangle(
            platforms[i].x,
            platforms[i].y,
            platforms[i].width,
            platforms[i].height,
            WHITE );
    }  

    if (paused){
        DrawText("PAUSED ",ball.x,ball.y,60,RED);
    }
    
    
       

    EndDrawing();

    EndMode2D();
        
    }
    
    
    CloseWindow();


}
