/*
 *  population
 *  Creator: Arlo Gittings
 *  Last Modified: 2021-04-02
 *  Description:
 *      Calculate the number of years it takes for a population of llamas to
 *      grow from a starting population to a target (both entered by the user.
 */

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    const int N_MIN = 9;    // minimum population
    const int LOSS = 4;     // number of dead llamas/year
    const int GAIN = 3;     // number of baby llamas/year
    int n_loss = 0;         // current year's lost llamas
    int n_gain = 0;         // current year's gained llamas
    int n_start = 0;        // starting population
    int n_target = 0;       // target population
    int n_current = 0;      // current population
    int years = 0;          // number of years since start population

    // 	Get user input for starting population; set current population equal
    while(n_start < N_MIN)
    {
        n_start = get_int("Enter starting population of %d or more: ", N_MIN);
    }
    n_current = n_start;

    //	Get user input for target population
    while(n_target < n_current)
    {
    n_target = get_int("Enter target population of %d or more: ", n_start);
    }

    while(n_current < n_target)
    {
        years++;
        n_loss = n_current / LOSS;
        n_gain = n_current / GAIN;
        n_current = n_current - n_loss + n_gain;
    }

    printf("Years: %d\n", years);

    return 0;
}
