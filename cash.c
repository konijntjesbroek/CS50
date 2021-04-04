/*
 *  cash
 *  creator: Arlo Gittings
 *  last modifed: 20214-04-04
 *                    |"| |"|
 *                    | |_| |
 *                   / o   o \
 *                  (    x    )
 *                   \ .   . /
 *                   "  "."  "
 *  description:
 *      determine the smallest number of coins to return to create change
 */

#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    float change = 0;
    int owed = 0;
    int q = 0;
    int d = 0;
    int n = 0;

    
    while(change <= 0)
    {
        change = get_float("Change owed: ");
    }

    owed = round(change * 100);
    
    while (owed >= 25)
    {
        q++;
        owed -= 25;
    }

    while (owed >= 10)
    {
        d++;
        owed -=10;
    }

    while (owed >= 5)
    {
        n++;
        owed -= 5;
    }
    
    printf("%d\n", q + d + n + owed);
    
    return 0;
}

