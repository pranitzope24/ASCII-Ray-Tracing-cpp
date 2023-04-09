#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <utility>
#include <stdio.h>
#include <math.h>
#include <Windows.h>

int nScreenWidth = 120;			// Console Screen Size X (columns)
int nScreenHeight = 40;			// Console Screen Size Y (rows)
int nMapWidth = 16;				// World Dimensions W
int nMapHeight = 16;            // World Dimensions H

float fPlayerX = 14.7f;		    // Player Start Position X
float fPlayerY = 5.09f;         // Player Start Position Y
float fPlayerA = 0.0f;			// Player Start Rotation
 
float fFOV = M_PI_4;	        // Field of View (pi/4) 

float fDepth = 16.0f;			// Maximum rendering distance
float fSpeed = 5.0f;


int main (int argc, char **argv){
    
    /**
     * Creating a screen buffer
     * Contains lot of things specific to windows, hence seems a bit complicated
     * used windows.h to create a buffer of size nScreenWidth X nScreenHeight
    */
    wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE,0,__null,CONSOLE_TEXTMODE_BUFFER,__null);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    //Creating the map
    std::wstring map;

    map+= L"###############";
    map+= L"#.............#";
    map+= L"#.............#";
    map+= L"#.............#";
    map+= L"#.............#";
    map+= L"#.............#";
    map+= L"#.............#";
    map+= L"#.............#";
    map+= L"#.............#";
    map+= L"#.............#";
    map+= L"#.............#";
    map+= L"#.............#";
    map+= L"#.............#";
    map+= L"#.............#";
    map+= L"#.............#";
    map+= L"#.............#";
    map+= L"###############";



    // Main loop
    while(true){
        //main content goes here


        //Display Frame
        screen[nScreenWidth*nScreenHeight-1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth*nScreenHeight, {0,0}, &dwBytesWritten);
    }

    return 0;
}