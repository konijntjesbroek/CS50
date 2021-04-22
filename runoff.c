#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
int next_choice(int voter);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

bool vote(int voter, int rank, string name)
{
    //  vote:
    //      validate candidate voted for and update preferences
    //          for the given voter and rank
    //      expects:
    //          voter: int, the voter id
    //          rank:  current ranking of given candidate
    //          name:  name of candidate voted for
    //      returns:
    //          true if candidate is validated, otherwise false

    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i].name))
        {
            preferences[voter][rank] = i;
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //  tabulate:
    //      count the number of votes for all candidates in the 
    //          current round of the election. 
    //      expects:
    //          none
    //      returns:
    //          none
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }
    
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < voter_count; j++)
        {
            if (preferences[j][0] == i)
            { 
                if (!candidates[i].eliminated)
                {
                    candidates[i].votes++;
                }
                else
                {
                    int n = next_choice(j);
                    if (n != -1)
                    {
                        candidates[n].votes++;
                    }
                }
            }
        }
    }
    return;
}

bool print_winner(void)
{
    //  print_winner:
    //      print the winner if one candidate has garnered > 50%
    //          of votes in the durrent round of voting.
    //      expects:
    //          none
    //      returns:
    //          none

    int current = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > candidates[current].votes)
        {
            current = i;
            if (candidates[i].votes > (voter_count / 2))
            {    
                printf("%s\n", candidates[i].name);
                return true;
            }

        }
    }
    return false;
}

int find_min(void)
{
    //  find_min:
    //      identify and return the lowest number of votes in this round
    //      expects:
    //          none
    //      returns:
    //          result: int, minimum number of votes
    int result = voter_count;
    
    for (int i = 0; i < candidate_count; i ++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < result)
        {
            result = candidates[i].votes;
        }
    }

    return result;
}

bool is_tie(int min)
{
    //  is_tie:
    //      return true if all remaining candidates have the same 
    //          number of votes.
    //      expects:
    //          min: int, the lowest number of votes
    //      returns:
    //          true if all remaining candidates tie, else false

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes > min)
        {
            return false;
        }
    }
    return true;
}

void eliminate(int min)
{
    //  eliminate:
    //      set candidates.eliminated for all candidates that have
    //          the lowest number of votes in this round.
    //      expects:
    //          min: int, the lowest number of votes
    //      returns:
    //          none
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}

int next_choice(int voter)
{
    //  next_choice:
    //      return the voters next valid choice or returns -1 if no
    //          valid choices remain.
    //      expects:
    //          voter:  int, voter ID for current list.
    //      returns:
    //          next valid candidate ID from current voter prefs

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[preferences[voter][i]].eliminated)
        {
            return preferences[voter][i];
        }
    }
    return -1;
}
