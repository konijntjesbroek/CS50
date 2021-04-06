/*
    scrabble
    creator: Arlo Gittings
    last modified: 2021-04-06
 */

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>


int compute_score(string word);

int main(void)
{   

    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    return 0;
}

int compute_score(string word)
{
    /*
        compute_score
        expects:
            word: string; user supplied word
        returns:
            score: int; numerical score based off scrabble tile scores
     */
    
    int word_length = strlen(word); 
    int sum = 0;
    int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
                    1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
                   };
    /*
        start at the first char in the string, skip it if it isn't a
        letter. Otherwise, subtract the base character for the given
        set to find the points in the above list
     */
    for (int i = 0; i < word_length; i++)
    {
        if (!isalpha(word[i])) 
        {
            continue;
        }
        else if (isupper(word[i]))
        {
            sum += POINTS[word[i] - 'A'];
        }
        else
        {
            sum += POINTS[word[i] - 'a'];
        }   
    }

    return sum;
}
