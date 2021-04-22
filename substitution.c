///////////////////////////////////////////////////////////////////////////////
//
//  subsitution
//  created: Arlo Gittings
//  last modified: 2021-04-08
//  description:
//      implementation of a substitu cipher 
//
///////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <ctype.h>
#include <cs50.h>

int parse_switch(char s[])
{
    /*
        parse_switch:
            validate the user supplied offset and return it.
            expects:
                s: [] char; the argument 
     */

    char result[26];


    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!isalpha(s[i]))
        {
            s[0] = '1';
        }

    }
    return result;
}

int transpose(string s, string t)
{
    ///////////////////////////////////////////////////////////
    //
    //  transpose:
    //      change the string s by p places to the left;
    //      expacts:
    //          s:  string; plaintext to encode
    //          p:  int; non-negative integer to shift the cipher
    //      returns:
    //          0 upon completion
    //
    /////////////////////////////////////////////////////////////

    printf("ciphertext: ");
    for (int i = 0; s[i] != '\0'; i ++)
    {
        if (isupper(s[i]))
        {
            printf("%c", (((s[i] + p) - 'A') % 26) + 'A');
        }
        else if (islower(s[i]))
        {
            printf("%c", (((s[i] + p) - 'a') % 26) + 'a');
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");

    return 0;
}
int main(int argc, char *argv[])
{
    int shift_width;


    if (argc == 2 && argv[1] != '\0')
    {
        shift_width = parse_switch(argv[1]);
    }
    else
    {
        shift_width = -1;
    }
    if (shift_width == -1)
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
    else
    {
        string plain_text = get_string("plaintext: ");
        return transpose(plain_text, shift_width);
    }
}
