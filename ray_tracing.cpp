#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <utility>
#include <stdio.h>
#include <math.h>
#include <Windows.h>

int screenWidth = 120;			// Console Screen Size X (columns)
int screenHeight = 40;			// Console Screen Size Y (rows)
int mapWidth = 16;				// World Dimensions W
int mapHeight = 16;             // World Dimensions H

float playerX = 8.0f;		    // Player Start Position X
float playerY = 8.0f;           // Player Start Position Y
float playerA = 0.0f;			// Player Start Rotation
// float playerA = M_PI_4;			
// float playerA = M_PI_2;			
// float playerA = 3*M_PI_4;			
 
float FOV = M_PI_4;	            // Field of View (pi/4) 

float depth = 16.0f;			// Maximum rendering distance
// float speed = 5.0f;             // Movement speed

typedef struct uvec {
    float X;
    float Y;
    //float Z;  //not needed for now
} uvec;


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
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"#..............#";
    map+= L"################";



    // Main loop
    while(true){
        
        // We will deal column wise hence a for loop for column operations
        for(int x=0; x< screenWidth; x++){

            //calculate the ray angle, and find the distance to the wall using a flag, and computing the eye angles
            float rayAngle = (playerA - FOV/2.0f) + ((float)x / (float)screenWidth) * FOV;
            float distanceToWall = 0; 
            bool hitWall = false;      

            //unit vector for ray
            uvec eye;
            eye.X = sinf(rayAngle);
            eye.Y = cosf(rayAngle);

            while (!hitWall && distanceToWall < depth){

                distanceToWall += 0.1f;  //small increment for more precision

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

            //now for ceiling, we can use simple geometry and trim portions form up and down symmetrically
            int ceiling = (float)(screenHeight/2.0) - screenHeight/((float)distanceToWall);
            int floor = screenHeight - ceiling;

            for(int y=0; y<screenHeight; y++){
                screen[y*screenWidth + x] = ((y<=ceiling)?' ':((y>ceiling&&y<=floor)?'#':' '));
            }

        }

        //Display Frame
        screen[screenWidth*screenHeight-1] = '\0';
		WriteConsoleOutputCharacterW(console, screen, screenWidth*screenHeight, {0,0}, &bytesWritten);
    }

    return 0;
}