# ASCII-Ray-Tracing-cpp

## Usage
Clone this repository and cd into it
```
make
./ray_tracing
```

*Controls*
* `W` - Forward
* `S` - Backward
* `A` - Left 
* `D` - Right

## Approach for Making

Firstly, `std::cout` isn't going to work since the time taken is much higher than directly writing on the console. Hence we will use conventional `printf` or similar methods and its variants for our main display.

### Made a screen buffer of size `120x40`
Using `windows.h` created a screen buffer using `createConsoleScreenBuffer()` and service to print directly onto it any desired manner using the coordinates using the `WriteConsoleOutputCharacter()` method.

### Made a basic Map
* Made a 16X16 map to move around and demonstrate the basic ray tracing
* `#` represent the wall
* `.` represent the empty space
<!-- * `P` represent the player position -->

### Initialised the main Game Loop
Just simply using `while(true)` for now for the continuous rendering.

## Algorithm
The following image contains the player, the wall and the FOV of the player in the game (red dotted line).

![Depiction of the algorithm](docs/potters_algo.png)

We calculate the distance to the wall by incrementing until the flag `bHitWall` becomes true. (Depicted by the blue dashed line).



