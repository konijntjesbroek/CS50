/*
 *  credit
 *  creator: Arlo Gittings
 *  last modified: 2021-04-03
 *  Description:
 *      Validate visa, mc, amex credit cards according to Luhn's algorithm
 *          1. multiply every other digit by 2 starting with 2nd to last
 *          2. add the digits of these products
 *          3. add the digits of that were not doubled
 *          4. add the doubled and non-doubled sums
 *          5. if the final sum is divisible by 10, it is plausible.
 *
 *      Test Conditions:
 *          1. amex:    digits: 15;     prefix: 3[4,7]
 *          2. mc:      digits: 16;     prefix: 5[1-5]
 *          3. visa:    digits: 13, 16; prefix: 4 
 */

#include <stdio.h>
#include <cs50.h>

int rough_check(unsigned long n)
{
    /*   
     *  rough_check:
     *      Determine if the entered card number is within known
     *      valid card ranges. This allows us to shortcut the 
     *      heavy lifting of Luhn's math if the card isn't one a
     *      known type.
     *  expects: 
     *      n: unsigned long, account ID  
     *  return: 
     *      result: int, numeric indicator of type of card
     *          0: INVALID    
     *          1: AMEX
     *          2: MASTERCARD
     *          3: VISA
     */

    // card ranges
    const unsigned long AMEX_LB = 340000000000000;  
    const unsigned long AMEX_LT = 349999999999999;
    const unsigned long AMEX_HB = 370000000000000;
    const unsigned long AMEX_HT = 379999999999999;
    const unsigned long MC_B    = 5100000000000000;
    const unsigned long MC_T    = 5599999999999999;
    const unsigned long VISA_LB = 4000000000000;
    const unsigned long VISA_LT = 4999999999999;
    const unsigned long VISA_HB = 4000000000000000;
    const unsigned long VISA_HT = 4999999999999999;
    // end of card ranges

    int result = 0;

    if ((n >= AMEX_LB && n <= AMEX_LT) || (n >= AMEX_HB && n <= AMEX_HT))
    {
        result = 1;    
    }
    else if (n >= MC_B && n <= MC_T)
    {
        result = 2;
    }
    else if ((n >= VISA_LB && n <= VISA_LT) || (n >= VISA_HB && n <= VISA_HT))
    {
        result = 3;
    }
    // test for setting card type printf("%d\n", result);    
    return result;
}

bool luhn_check(unsigned long n)
{
    /* 
     *  luhn_check:
     *      alternate additions of digits:
     *        last digit (ld) 
     *      + sum of digits (2 * (ld - 1)) 
     *      + ld - 2
     *      + sum of digits (2 * (ld - 3))
     *      ... first digit if odd, else sum of digits(2 * fd)
     *      expect:
     *          n: unsigned long; account id of card holder
     *      return: 
     *          true if luhn_value % 10, else false  
     */ 

    int luhn_value = 0;
    int counter = 0;
    int current = 0;

    while (n > 0)
    {
        if (counter % 2) // maths for every other digit staring with ld - 1
        {
            current = 2 * (n % 10);
            if (current > 9)
            {
                current = (current % 10) + current / 10;
            }
        }
        else 
        {
            current = n % 10;
        }
        
        // test for math printf("\t%d\t%d\n", luhn_value, current);
        luhn_value += current;
        n = n / 10;
        counter++;
    }
    
    if (luhn_value % 10)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void print_card(int t)
{
    /*
     *  print_card:
     *      print out the card type
     *  expects:
     *      t: int; type mask
     *  returns:
     *      none
     */

    switch (t)
    {
        case 1:
            printf("AMEX\n");
            break;

        case 2:
            printf("MASTERCARD\n");
            break;
        
        case 3:
            printf("VISA\n");
            break;
        
        default:
            printf("INVALID\n");
    }

} 

int main(void)
{
    unsigned long card_num = get_long("Number: ");  // get the card number
    int card_type = rough_check(card_num); // numeric mask for cards
   
    if ((card_type) && (!luhn_check(card_num))) // magic
    {
        card_type = 0;
    }

    print_card(card_type);

    return 0;
}


