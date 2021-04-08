/*
    readability
    creator: Arlo Gittings
    last modified: 2021-04-07
    description:
        determine the reading level for a user submitted string based on the 
        Coleman-Liau index:
            Reading Level = .0588 * average number of letters per 100 words
                          - .296 * average number of sentences per 100 words
                          - 15.8
 */

#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int alt_calc(string s)
{
    /*
        alt_calc:
            calculate the coleman-liau index of a user submitted
            passage using simplified markers for words and sentences

            expects:
                s:  string; a string of letters, punctuation and whitespace
            returns:
                level: int (0-16); the reading level of s rounded to the
                       the nearest grade
     */    

    int letter = 0;
    int word = 1;
    int sent = 0;
    
    // calculate the letters, words, sentences
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (isalpha(s[i]))
        {
            letter++;
        }
        else if (s[i] == ' ')
        {
            word++;
        }
        else if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sent++;
        }


    }

    
    //    calculate the precursors with cross multiplication
    //        x / word = L/100
     

    float L = (100.0 * letter) / word;
    float S = (100.0 * sent) / word; 
    int level = round(0.0588 * L - 0.296 * S - 15.8);

    if (level < 1)
    {
        level = 0;
    }
    else if (level > 16)
    {
        level = 16;
    }
    return level;
}

int main(void)
{
    string test_text = get_string("Text: ");
    int level = alt_calc(test_text);
    
    // force edge cases
    if (level == 0)
    {
        printf("Before ");
        level++;
    }
    
    printf("Grade %i", level);
    if (level == 16)
    {
        printf("+\n");
    }
    else
    {
        printf("\n");
    }
    return 0;
}

