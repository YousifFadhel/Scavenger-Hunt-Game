#include <stdio.h>
#include "MacUILib.h"
#include "myStringLib.h"   // This is your first custom C library

// [TODO] Import the required library for rand() and srand()
// [TODO] Import the required library for accessing the current time - for seeding random number generation

#include <stdlib.h>
#include <time.h>




// PREPROCESSOR DIRECTIVE CONSTANTS
// ================================
// For program-wide constants, define them here using #define.  Add as seen needed.


// [TODO] Then, define more constants here as seen needed.

#define X 20
#define Y 10
#define num 5




// GLOBAL VARIABLES
// ================================

int exitFlag; // Program Exiting Flag

// [COPY AND PASTE FROM PPA2] Copy your additional global from PPA2 and paste them below

// [TODO] Declare More Global Variables as seen needed.

// [TODO] Declare Global Pointers as seen needed / instructed in the manual.

const char *GoalString = "McMaster-ECE"; // Declaring a constant string

char *MysteryString; // Declaring a character array pointer


int i, j, k, l, speed_setting;
int xpos = 0;
int ypos = 0;



struct objPos
{
    int x;
    int y;
    char symbol;
};
struct objPos player;

struct objPos* ItemBin;

enum player_direction {up = 'w', down = 's', left = 'a', right = 'd', still = '0'};

enum player_direction dir;
enum player_direction prevdir = still;

enum game_speed {very_slow = 800000, slow = 400000, medium = 220000, fast = 100000, very_fast = 55000}; // Less delay will result in faster speed setting.
enum game_speed speed = medium;

char board[10][20] = {0};

struct objPos * ItemBin; // Declaring a struct objPos pointer

int moveCount = 0;



int exitFlag; // Program Exiting Flag - old stuff

// For storing the user input - from PPA1
char input;




// FUNCTION PROTOTYPES
// ================================
// Declare function prototypes here, so that we can organize the function implementation after the main function for code readability.

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// [TODO] In PPA3, you will need to implement this function to generate random items on the game board
//        to set the stage for the Scavenger Hunter game.
// list[]       The pointer to the Item Bin
// listSize     The size of the Item Bin (5 by default)
// playerPos    The pointer to the Player Object, read only.
// xRange       The maximum range for x-coordinate generation (probably the x-dimension of the gameboard?)
// yRange       The maximum range for y-coordinate generation (probably the y-dimension of the gameboard?)
// str          The pointer to the start of the Goal String (to choose the random characters from)
void GenerateItems(struct objPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, const char* str);


// MAIN PROGRAM
// ===============================
int main(void)
{

    Initialize();

    while(!exitFlag)  
    {
        GetInput();

        RunLogic();

        DrawScreen();

        LoopDelay();
    }

    CleanUp();

}




// INITIALIZATION ROUTINE
// ===============================
void Initialize(void)
{

    // [COPY AND PASTE FROM PPA2] Copy your initialization routine from PPA2 and paste them below

    MacUILib_init();
    MacUILib_clearScreen();

    input = 0; // NULL
    exitFlag = 0;  // not exiting    
   
    // [TODO] : Initialize more variables here as seen needed.
    //          PARTICULARLY for the structs!!

    player.symbol = '@';
    player.x = 8;
    player.y = 3;


    MysteryString = (char *)malloc(my_strlen(GoalString) + 1); // allocating memory on the heap for the MysteryString

    for (k = 0; k < my_strlen(GoalString); k++) // Populating all characters in MysteryString with ? except the null character.
    {
        MysteryString[k] = '?';   // MEMORY UNSAFE *******
    }

    ItemBin = (struct objPos *)malloc(5 * sizeof(struct objPos)); // Allocating space in the heap to hold 5 struct objPos instances, Memory Unsafe***


    
    // [TODO] Initialize any global variables as required.
    exitFlag = 0;  // 0 - do not exit, non-zero - exit the program

    
    // [TODO] Allocated heap memory for on-demand variables as required.  Initialize them as required.

    // [TODO] Seed the random integer generation function with current time.

    srand(time(NULL));

    // [TODO] Generate the initial random items on the game board at the start of the game.
    GenerateItems(ItemBin, num, &player, X, Y, GoalString);

    
}



// INPUT COLLECTION ROUTINE
// ===============================
void GetInput(void)
{

    // Asynchronous Input - non blocking character read-in
    
    // [COPY AND PASTE FROM PPA2] Copy your input collection routine from PPA2 and paste them below

    // [TODO] Though optional for PPA3, you may insert any additional logic for input processing.

    
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }



   
}




// MAIN LOGIC ROUTINE
// ===============================
void RunLogic(void)
{
    // [COPY AND PASTE FROM PPA2] Copy your main logic routine from PPA2 and paste them below

    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case ' ':  // exit
                exitFlag = 1;
                break;
            case (up):
                dir = up;
                break;
            
            case (down):
                dir = down;
                break;

            case (left):
                dir = left;
                break;

            case (right):
                dir = right;
                break;
            
            case (49):
                speed = very_slow;
                speed_setting = 1;
                break;
            
            case (50):
                speed = slow;
                speed_setting = 2;
                break;

            case (51):
                speed = medium;
                speed_setting = 3;
                break;

            case (52):
                speed = fast;
                speed_setting = 4;
                break;

            case (53):
                speed = very_fast;
                speed_setting = 5;
                break;
            
        

            // Add more key processing here
            // Add more key processing here
            // Add more key processing here    


            default:
                break;
        }
        input = 0;
    }



    if (ypos == 0)
    {
        ypos = 9;
    }

    if (xpos == 0)
    {
        xpos = 19;
    }




    // [TODO]   Implement the Object Collision logic here
    //
    //      Simple Collision Algorithm
    //      1. Go through all items on board and check their (x,y) against the player object x and y.
    //      2. If a match is found, use the ASCII symbol of the collided character, and 
    //         find all the occurrences of this ASCII symbol in the Goal String
    //      3. For every occurrence, reveal its ASCII character at the corresponding location in the
    //         Collected String
    //      4. Then, determine whether the game winning condition is met.

    for (i = 0; i < num; i++)
    {
        if (ItemBin[i].x == (((player.x + xpos) % 18) + 1) && ItemBin[i].y == (((player.y + ypos) % 8) + 1))      
        {
            
            for (j = 0; j <= my_strlen(GoalString); j++) // original
            {
                if (ItemBin[i].symbol == GoalString[j])
                {
                    MysteryString[j] = ItemBin[i].symbol; 
                }

                if (my_strcmp(MysteryString, GoalString) == 1)
                {
                    exitFlag = 1;
                }

            }
            GenerateItems(ItemBin, num, &player, X, Y, GoalString);
        }
    }





    // [TODO]   Implement Game Winning Check logic here
    //
    //      Game Winning Check Algorithm
    //      1. Check if the contents of the Collected String exactly matches that of the Goal String.
    //         YOU MUST USE YOUR OWN my_strcmp() function from Lab 3.
    //      2. If matched, end the game.
    //      3. Otherwise, discard the current items on the game board, and 
    //         generate a new set of random items on the board.  Game continues.


}





// DRAW ROUTINE
// ===============================
void DrawScreen(void)
{
       
    // [COPY AND PASTE FROM PPA2] Copy your draw logic routine from PPA2 and paste them below


    MacUILib_clearScreen();

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (i == 0 || i == 9)
            {
                board[i][j] = '#';  // formatting boarders of the display.
            }
            else if (j == 0 || j == 19)
            {
                board[i][j] = '#'; // formatting boarders of the display.
            }

            else
            {
                board[i][j] = ' ';
            }

            board[((player.y + ypos) % 8) + 1][((player.x + xpos) % 18) + 1] = player.symbol;
            for (int l = 0; l < num; l++) 
            {
                board[ItemBin[l].y][ItemBin[l].x] = ItemBin[l].symbol;
            }
            MacUILib_printf("%c", board[i][j]);
        }

        MacUILib_printf("\n");
        
    }

    MacUILib_printf("Please Enter A Number From 1-5 to Select the Speed of the Game\n");
    MacUILib_printf("Mystery String: %s\n", MysteryString);
    MacUILib_printf("Speed: %d\n", speed_setting);
    




    switch (dir)
    {
        case (up):
            if (prevdir != down)
            {
                ypos--;
                prevdir = up;
                MacUILib_printf("Direction: UP\n"); // Direction indicator as shown in the sample submission.
                moveCount++;
            }
            else
            {
                ypos++;
                moveCount++;
            }
            break;

        case (down):
            if (prevdir != up)
            {
                ypos ++;
                prevdir = down;
                MacUILib_printf("Direction: DOWN\n");
                moveCount++;
            }
            else
            {
                ypos--;
                moveCount++;
            }
            break;
        
        case (left):
            if (prevdir != right)
            {
                xpos--;
                prevdir = left;
                MacUILib_printf("Direction: LEFT\n");
                moveCount++;
                
            }
            else
            {
                xpos++;
                moveCount++;
            }
            break;

        case (right):
            if (prevdir != left)
            {
                xpos++;
                prevdir = right;
                MacUILib_printf("Direction: RIGHT\n");
                moveCount++;
            }
            else
            {
                xpos--;
                moveCount++;
            }
            break;
            


        default:
            break;

    }

    MacUILib_printf("Move Count: %d\n", moveCount);

    //  3. For every visited character location on the game board
    //          If on border on the game board, print a special character
    //          If at the player object position, print the player symbol
    //          Otherwise, print the space character
    //     Think about how you can format the screen contents to achieve the
    //     same layout as presented in the lab manual

    //  4. Print any debugging messages as seen needed below the game board.
    //     As discussed in class, leave these debugging messages in the program
    //     throughout your dev process, and only remove them when you are ready to release
    //     your code. 

    if (exitFlag == 1)
    {
        MacUILib_printf("****You WIN!:D****\n");
    }
   








    // [TODO]   Insert somewhere in the draw routine to draw the randomly generated items on the board.

    // [TODO]   Display the "Mystery String" contents at the bottom of the game board
    //          To help players keep track of their game progress.
    
    
    
}



// DELAY ROUTINE
// ===============================
void LoopDelay(void)
{
    MacUILib_Delay(100000); // 0.1s delay
}





// TEAR-DOWN ROUTINE
// ===============================
void CleanUp(void)
{
    // [TODO]   To prevent memory leak, free() any allocated heap memory here
    //          Based on the PPA3 requirements, you need to at least deallocate one heap variable here.

    // Insert any additional end-game actions here.

    free(MysteryString);

    free(ItemBin);
    

    MacUILib_uninit();
}




// The Item Generation Routine
////////////////////////////////////
void GenerateItems(struct objPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, const char* str)
{
    // This is possibly one of the most conceptually challenging function in all PPAs
    // Once you've mastered this one, you are ready to take on the 2SH4 course project!

    // Random Non-Repeating Item Generation Algorithm
    ////////////////////////////////////////////////////

    // Use random number generator function, rand(), to generate a random x-y coordinate and a random choice of character from the Goal String as the ASCII character symbol.
    //      The x and y coordinate range should fall within the xRange and yRange limits, which should be the x- and y-dimension of the board size.
    // This will then be a candidate of the randomly generated Item to be placed on the game board.

    // In order to make sure this candidate is validated, it needs to meet both criteria below:
    //  1. Its coordinate and symbol has not been previously generated (no repeating item)
    //  2. Its coordinate does not overlap the Player's position
    // Thus, for every generated item candidate, check whether its x-y coordinate and symbol has previously generated.  
    //  Also, check if it overlaps the player position
    //      If yes, discard this candidate and regenerate a new one
    //      If no, this candidate is validated.  Add it to the input list[]

    // There are many efficient ways to do this question
    //  We will take a deep dive into some methods in 2SI.
    

    struct objPos Canditate;
    int counter = 0;
    int candCord[X][Y] = {0};
    int i, j;
    int isUnique, CharCount = 0;
    int UsedSym[num] = {0};


    while (counter < listSize)
    {
        Canditate.y = 1 + rand() % (yRange - 2); //subtracting the borders
        Canditate.x = 1 + rand() % (xRange - 2);


    // Check whether the canditate coordinate matches the player location or the location of another item.

        if (candCord[Canditate.x][Canditate.y] == 0 && Canditate.x != (*playerPos).x && Canditate.y != (*playerPos).y)
        {
            candCord[Canditate.x][Canditate.y]++;
        }

        else
        {
            continue;
        }

        do
        {
            if (counter <= 1)
            {
            i = rand() % my_strlen(GoalString);
            Canditate.symbol = GoalString[i];
            isUnique = 1;

            for (j = 0; j < CharCount; j++)
            {
                if (Canditate.symbol == UsedSym[j])
                {
                    isUnique = 0;
                    break;
                }
            }

            if (isUnique)
            {
                UsedSym[CharCount] = Canditate.symbol;
                CharCount++;
            }
            }

        } while (!isUnique && (CharCount < num));

        do
        {
            if (counter > 1)
            {
            i = rand() % (127 - 33) + 33;
            while (i == 64 || i == 32 || i == 35 || i == 77 || i == 99 || i == 97 || i == 115 || i == 116 || i == 101 || i == 114 || i == 45 || i == 69 || i == 67)
            {
                i = rand() % (127 - 33) + 33;
            }

            Canditate.symbol = i;
        

            for (j=2; j < CharCount; j++)
            {
                if (Canditate.symbol == UsedSym[j])
                {
                    isUnique = 0;
                    break;
                }
            }

            }

        } while (!isUnique && (CharCount < num));







        

        list[counter] = Canditate;
        counter++;

    }




}

