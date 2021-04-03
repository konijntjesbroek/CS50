/*
 *  mario
 *  Creator: Arlo Gittings
 *  Last Modified: 2021-04-03
 *  Description:
 *      Create a pyramid of # symbols for values between 1 and 8
 *      there will be a gully of 2 spaces between the central blocks.
 */

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    const int H_MIN = 1;    // minimum height allowed
    const int H_MAX = 8;    // maximum height allowed
    const int GULLY = 2;    // gully width
    int height = 0;         // height of the tower
    int spaces = 0;         // number of blocks before level
    int level = 0;          // number of blocks in current level
    int current = 0;        // the current block number
    int gully_blocks = 0;   // gulley counter allows for widening of the gap.

    while (height < H_MIN || height > H_MAX)
    {
        height = get_int("Height: ");
    }

    for (level = 1; level <= height; level++)
    {
        for (spaces = height - level; spaces > 0; spaces--)
        {
            printf(" ");
        }
        
        for (current = 0; current < level; current++)
        {
            printf("#");
        }
        
        for (gully_blocks = 0; gully_blocks < GULLY; gully_blocks++)
        {
            printf(" ");
        }
        
        for (current; current > 0; current--)
        {
            printf("#");
        }
        
        printf("\n");
    }

    return 0;
}
