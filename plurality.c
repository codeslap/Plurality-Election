#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;
// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");


    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
            //if vote is invalid, ask again for name until valid name is entered
            while (vote(name) == false)
            {
                name = get_string("Vote: ");

            }
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        //checking string of input to candidate list for match
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    //if no match return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //array to keep track of highest votes
    int high[] = {0};
    //array to keep track of ties, later will change 0s to 1s if tied
    int tie[] = {0,0,0,0,0,0,0,0,0};
    // variable win will keep track of candidate with highest votes
    int win = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {

        if (candidates[i].votes > candidates[j].votes && candidates[i].votes > high[0])
        {
            //update high[0] only if above statements are correct which means new highest votes
            high[0] = candidates[i].votes;
            win = i;

        }
        if (candidates[j].votes > candidates[i].votes && candidates[j].votes > high[0])
        {
            high[0] = candidates[j].votes;
            win = j;

        }
        if (candidates[i].votes == candidates[j].votes && j != i)
        {
            //if there is a tie, update tie array to keep track of ties
            tie[i] = 1;
            tie[j] = 1;
        }
        // getting ready to print once i and j for loops are at the end
        if (i == (candidate_count - 1) && j == (candidate_count -1))
            {
                // before printing 1 winner, check for ties
                for (int p = 0; p < candidate_count; p++ )
                {
                    if (tie[p] == 1 && candidates[p].votes >= candidates[win].votes)
                    {
                        printf("%s\n", candidates[p].name);
                        if (p == candidate_count -1)
                        {
                            return;
                        }
                    }
                }
                //if no ties, then print the candidate with the most points
                printf("%s\n", candidates[win].name);
                return;
            }
        }
        }
    }

