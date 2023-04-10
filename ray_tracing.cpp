#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <utility>
#include <stdio.h>
#include <math.h>
#include <Windows.h>
typedef struct uvec {
    float X;
    float Y;
    //float Z;
} uvec;

int screenWidth = 120;			// Console Screen Size X (columns)
int screenHeight = 40;			// Console Screen Size Y (rows)

int mapWidth = 16;				// World Dimensions W
int mapHeight = 16;             // World Dimensions H

float playerX = 8.0f;		    // Player Start Position X
float playerY = 8.0f;           // Player Start Position Y
float playerA = 0.0f;			// Player Start Rotation	
 
float FOV = M_PI_4;	            // Field of View (pi/4) 
float depth = 16.0f;			// Maximum rendering distance

float movSpeed = 5.0f;          // Movement speed
float angSpeed = 1.2f;          // Angular speed


char shade(float __dist);

int main (int argc, char **argv){
    
    /**
     * Creating a screen buffer
     * Contains lot of things specific to windows, hence seems a bit complicated
     * used windows.h to create a buffer of size screenWidth X screenHeight
    */
    wchar_t *screen = new wchar_t[screenWidth*screenHeight];
    HANDLE console = CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE,0,__null,CONSOLE_TEXTMODE_BUFFER,__null);
    SetConsoleActiveScreenBuffer(console);
    DWORD bytesWritten = 0;

    //Creating the map
    std::wstring map;

    map+= L"################";
    map+= L"#........#.....#";
    map+= L"#........#.....#";
    map+= L"#........#.....#";
    map+= L"#........#.....#";
    map+= L"#..#.....#.....#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#...##.####....#";
    map+= L"#...#..........#";
    map+= L"#...#..........#";
    map+= L"#...#..........#";
    map+= L"#..............#";
    map+= L"################";
 

    auto t1 = std::chrono::system_clock::now();
    auto t2 = std::chrono::system_clock::now();

    // Main loop
    while(true){
        
        t2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedFrameTime = t2-t1;
        t1 = t2;
        float frameTime = elapsedFrameTime.count();


        if(GetAsyncKeyState('A') & 0x8000){
            playerA -= angSpeed * frameTime;
        }
        if(GetAsyncKeyState('D') & 0x8000){
            playerA += angSpeed * frameTime;
        }
        if(GetAsyncKeyState('W') & 0x8000){
            playerX +=  sinf(playerA) * movSpeed * frameTime;
            playerY +=  cosf(playerA) * movSpeed * frameTime;
            if(map[(int)playerY*mapWidth + (int)playerX] == '#') {
                playerX -=  sinf(playerA) * movSpeed * frameTime;
                playerY -=  cosf(playerA) * movSpeed * frameTime;
            }
        }
        if(GetAsyncKeyState('S') & 0x8000){
            playerX -=  sinf(playerA) * movSpeed * frameTime;
            playerY -=  cosf(playerA) * movSpeed * frameTime;
            if(map[(int)playerY*mapWidth + (int)playerX] == '#'){
                playerX +=  sinf(playerA) * movSpeed * frameTime;
                playerY +=  cosf(playerA) * movSpeed * frameTime;
            }
        }

        // We will deal column wise hence a for loop for column operations
        for(int x=0; x< screenWidth; x++){

            // calculate the ray angle, and find the distance to the wall using a flag, and computing the eye angles
            float rayAngle = (playerA - FOV/2.0f) + ((float)x / (float)screenWidth) * FOV;
            float distanceToWall = 0; 
            bool hitWall = false;      

            // unit vector for ray
            uvec eye;
            eye.X = sinf(rayAngle);
            eye.Y = cosf(rayAngle);

            while (!hitWall && distanceToWall < depth){

                distanceToWall += 0.1f;  // small increment for more precision

                int testX = (int)(playerX + ((eye.X)*distanceToWall));
                int testY = (int)(playerY + ((eye.Y)*distanceToWall));

                // check the position wrt boundaries of map 
                if(testX<0 || testX>=mapWidth || testY<0 || testY>=mapHeight){
                    hitWall = true;
                    distanceToWall = depth;
                }
                else if( map[(testY*mapWidth) + testX] == '#'){
                    hitWall = true;
                    // distanceToWall value is retained (originally increment one)
                }
                
            }

            // now for ceiling, we can use simple geometry and trim portions form up and down symmetrically
            // NOTE : y calculated from top to bottom
            int ceiling = (float)(screenHeight/2.0f) - screenHeight/((float)distanceToWall);
            int floor = screenHeight - ceiling;



            short shadeChar = ' ';

            if(distanceToWall <= depth/4.0f){
                shadeChar = 0x2588;
            }
            else if (distanceToWall < depth/3.0f){
                shadeChar = 0x2593;
            }
            else if (distanceToWall < depth/2.0f){
                shadeChar = 0x2592;
            }   
            else if (distanceToWall < depth){
                shadeChar = 0x2591;
            }   
            else {
                shadeChar = ' ';
            }



            for(int y=0; y<screenHeight; y++){
                if(y <= ceiling){
                    screen[y * screenWidth + x] = ' ';
                }
                if(y > ceiling && y <= floor){
                    screen[y * screenWidth + x] = shadeChar;
                }
                else { //floor shading
                    float floorRatio = 1.0f - (((float)y -screenHeight/2.0f) / ((float)screenHeight / 2.0f));
                    char floorShade = ' ';
                    
                    if (floorRatio<0.25){
                        floorShade = '#';
                    }
                    else if(floorRatio<0.5){
                        floorShade = 'x';
                    }
                    else if(floorRatio<0.75){
                        floorShade = '.';
                    }
                    else if(floorRatio<0.5){
                        floorShade = '-';
                    }
                    else {
                        floorShade = ' ';
                    }
                    screen[y*screenWidth + x] = floorShade;
                    // screen[y*screenWidth + x] = ' ';
                }
            }

        }

        //Display Frame
        screen[screenWidth*screenHeight-1] = '\0';
		WriteConsoleOutputCharacterW(console, screen, screenWidth*screenHeight, {0,0}, &bytesWritten);
    }

    return 0;
}