#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX]; //
// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool isCycle(int winner, int loser); // checks if the cycle exists

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    /*

        Run the loop for the number of candidates and compare the parameter 'name' with names stored in
        the candidates array through the function strcmp. If name is found, add the candidate represented by i
        to the ranks array.

        Note: ranks[rank] represent voter's rank'th preference

    */
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    /*
        This function has to label the preferences of each voter for candidates. It would run each time a new voter votes.
        In the ranks array the candidates are already sorted in descending order of preference.
        ranks[i] represents the user’s ith preference.

        In this function we need to increment the 2d preferences array by setting out the preference of ith candidate over jth
        candidate. Recall preferences[i][j] should represent the number of voters who prefer candidate i over candidate j.

        Since, the candidates are already arranged in descending order in the ranks array we use ranks[i] & ranks[j] in the
        loop as an index of preference array to be incremented
    */
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    /*
        Adding winner & loser in the pairs array by comparing preferences[i][j] with preferences[j][i]
    */
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].loser = i;
                pairs[pair_count].winner = j;
                pair_count++;

            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // Selection Sort
    int tempi, tempj;

    for (int i = 0; i < candidate_count; i++)
    {
        int max = -1000;

        /*
            Finding the greatest number from 'j' to 'candidate_count-1'
            j would be incremented after every completion through i
        */

        for (int j = i; j < candidate_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > max)
            {
                max = preferences[pairs[j].winner][pairs[j].loser];
                tempj = j;
                tempi = i;
            }
        }
        pair temp = pairs[tempj]; // Initialised new array 'temp' of type 'pair' to store winner & loser temporarily for the swap
        pairs[tempj] = pairs[tempi];
        pairs[tempi] = temp;
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int count = 0;
    for (int i = 0; i < pair_count; i++)
    {
        if (!(isCycle(pairs[i].winner, pairs[i].loser)))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

bool isCycle(int winner, int loser)
{
    if (winner == loser)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i]) // if the loser is the winner of any pair
        {
            if (isCycle(winner, i))
                /*
                checking that the cycle exists by sending winner and loser of
                the locked pair above. The i being sent here as an argument
                would be the loser candidate and if that is locked too - over
                some other candidate then the loser of that locked pair would be
                sent as 'i' to the function and if cycle is there; probably the
                loser would be equal to the winner of the case being checked, which
                would confirm the presence of cycle existing.
                */
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    bool status = true;
    string winner;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j]) // i is the winner
            {
                for (int k = 0; k < candidate_count; k++) // In this loop we will check if 'i' lost to someone, i.e., edge is pointing towards i
                {
                    status = true;
                    if (locked[k][i]) // if 'i' is found to be losing over 'k' we will move on to the next candidate by incrementing 'i'
                    {
                        status = false;
                        i++;
                        j = 0;
                        break;
                    }
                }
                if (status) // if 'i' is the actual winner then print out its name and increment 'i' to check for other candidates
                {
                    printf("%s", candidates[i]);
                    i++;
                    j = 0;
                }

            }
        }
    }
    printf("\n");
    return;
}

