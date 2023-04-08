#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <utility>
#include <stdio.h>
#include <math.h>

int nScreenWidth = 120;			// Console Screen Size X (columns)
int nScreenHeight = 40;			// Console Screen Size Y (rows)
int nMapWidth = 16;				// World Dimensions W
int nMapHeight = 16;             // World Dimensions H

float fPlayerX = 14.7f;			// Player Start Position X
float fPlayerY = 5.09f;          // Player Start Position Y
float fPlayerA = 0.0f;			// Player Start Rotation
 
float fFOV =  M_PI_4;	        // Field of View (pi/4) 

float fDepth = 16.0f;			// Maximum rendering distance
float fSpeed = 5.0f;

using namespace std;

int main (int argc, char **argv){
    printf("Hello");
    return 0;
}