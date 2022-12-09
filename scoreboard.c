#include "helpers.h"

// Needed constants
#define SCOREBOARD_X 39.0f

typedef struct _score 
{
    char name[4];
    int points;
} score;

// init scores to be all zero
score scores[3] = {{{"---"}, 0}, {{"---"}, 0}, {{"---"}, 0}};

/**
 * Displays the scoreboard: 3 scores, each with a name and a score
 */
void display_scoreboard() 
{
    v2 pos = {SCOREBOARD_X, 0.0};
    prints("SCOREBOARD", pos);
    pos._2 += LETTER_HEIGHT+1;
    pos._1 = 0;

    int i;
    for(i = 0; i < 3; i++) {
        printsn(scores[i].name, scores[i].points, pos);
        pos._2 += LETTER_HEIGHT+1;
    }
}
/**
 * Displays the current amount of points in-game
 */
void display_points() 
{
    printn(points, VZERO);
}

/**
 * Adds a player name and amount of points to the scoreboard 
 * 
 * @param name Name of the player as a 3 letter string
 * @param points Amount of points the player earned
 */
void add_score(char *name, int points) 
{
    if(points < scores[2].points) 
    {
        // Not enough points to be displayed
        return;
    }
    int i;
    for(i = 0; i < 3; i++) 
    {
        if(points >= scores[i].points) 
        {
            int j;
            for(j = 2; j > i; j--) 
            {
                scores[j] = scores[j-1];
            }
            scores[i].points = points;
            for(j = 0; j < 3; j++) 
            {
                // IMPORTANT: the global name variable has spaces
                // between each letter, therefore we pick name[0], name[2], name[4]
                scores[i].name[j] = name[j*2]; 
            }
            break;
        }
    }
}
