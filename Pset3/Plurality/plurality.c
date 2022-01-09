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
        //printf("%s", candidates[i].name);
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
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int greatest_score = 0;
    string winning_candidates[candidate_count]; // Array that would store the name(s) of winning candidate(s)
    int j = 0;
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > greatest_score)
        {
            greatest_score = candidates[i].votes; // Using the variable greatest_score to find the candidate with max votes
            
            /*
                The following 'if' condition is made for the case of 'tie' in votes that is now broken by a candidate who 
                received more votes than the candidates who had same votes.
                
                For example, if there are 3 candidates; 
                Alice, Bob & Charles.
                
                There are 7 voters. When 6 voters cast the vote the scenario is that each candidate received equal votes,
                i.e, 2 votes. Now the array winning_candidates stores the name of all 3 of these candidates. 
                
                However, 7th voter casts vote in favour of Charles. So we need to remove the names of other two candidates
                from the array and initialize 'j' to zero so when we are displaying the winning candidate(s), only the 1st 
                index of the memory is accessed.
                
            */
            
            if (j > 0)
            {
                for (int k = 0; k < j; k++)
                {
                    winning_candidates[j] = "";
                }
                j = 0;
            }
            winning_candidates[j] = candidates[i].name;
        }
        else if (candidates[i].votes == greatest_score)
        {
            j++;
            winning_candidates[j] = candidates[i].name;
        }
    }
    // Displaying the candidate(s) who won
    for (int i = 0; i <= j; i++)
    {
        printf("%s\n", winning_candidates[i]);
    }



}

