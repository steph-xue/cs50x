// The 'tideman' program gets the user to input the candidate names in a list as command-line arguments (max 9)
// It then prompts the user to input the number of voters and each person's ranking of votes (all candidates must be valid and listed at least once)
// It uses ranked pairs to determine the winner and then prints it out onto the screen

// The Tideman voting method consists of 3 parts:
    // Tally: Once all of the voters have indicated all of their preferences, determine, for each pair of candidates, who the preferred candidate is and by what margin they are preferred.
    // Sort: Sort the pairs of candidates in decreasing order of strength of victory, where strength of victory is defined to be the number of voters who prefer the preferred candidate.
    // Lock: Starting with the strongest pair, go through the pairs of candidates in order and “lock in” each pair to the candidate graph, so long as locking in that pair does not create a cycle in the graph.

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// The preferences[i][j] array stores the number of voters who prefer i over j
int preferences[MAX][MAX];

// The locked[i][j] array means i is locked in over j (gives graph where i has a locked in arrow winning over j)
bool locked[MAX][MAX];

// Each pair has a winner, loser (integer specifies candidate index)
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates (names)
string candidates[MAX];

// Array of pairs (with candidate index as winner/loser)
pair pairs[MAX * (MAX - 1) / 2];

// Number of pairs that are not tied and have a clear winner (in the pairs array determined later on)
// Sets initial number of pairs as 0 so we can add the number of pairs that are not tied and have a clear winner (after determining this)
int pair_count = 0;

// Total number of candidates inputed initially in the command-line
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool cycle(int winner, int loser);
void print_winner(void);

int main(int argc, string argv[])
{
    // Reminds user if they did not type any candidate names as command-line arguments
    if (argc < 2)
    {
        printf("Usage: ./tideman [candidate 1] [candidate 2] [...]\n");
        return 1;
    }

    // Sets the candidate count as the number of candidate names inputed as command-line arguments
    candidate_count = argc - 1;

    // Reminds the user of the maximum number of candidates if they typed in more than the maximum allowed
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // Populate array of candidates using the names typed as command-line arguments
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs (sets all initially as false or unlocked)
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    // Gets the user to input the number of voters
    int voter_count = get_int("Number of voters: ");

    // Gets each voter to input their ranking list
    for (int i = 0; i < voter_count; i++)
    {
        // Tells the user which voter is up next
        printf("Voter %i\n", i+1);

        // Creates a temporary array for the current voter to rank each candidate, where ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Iterates through each ranking for the voter
        for (int j = 0; j < candidate_count; j++)
        {
            // Gets the voter to input a name for each rank (must include all candidates in rankings)
            string name = get_string("Rank %i: ", j + 1);

            // Determines if the vote is valid (one of the candidates listed) and if so, stores the vote in ranks array for the voter
            if (!vote(j, name, ranks))
            {
                // If the vote is not valid (not one of the candidates), it tells the user the vote is invalid and exits the program
                printf("Invalid vote.\n");
                return 3;
            }
        }

        // Records the ranking list for each voter into the global paired preferences array (counts votes for 1 vs 1 candidates)
        record_preferences(ranks);

        printf("\n");
    }

    // Record pairs of candidates where one is preferred over the other (no tie) into the pairs array with a winner and loser (recorded as the candidate index)
    // Also tallies up the number of valid pair counts (no tied pairs included)
    add_pairs();

    // Sort pairs in decreasing order by strength of victory (strength is the difference between the number of 1 vs 1 votes between the pair)
    // Selection sort is done in this case
    sort_pairs();

    // Lock pairs into the candidate graph in order (highest to lowest strengths), without creating cycles
    lock_pairs();

    // Print the winner of the election (winner has no locked arrows pointing at itself)
    print_winner();
    return 0;
}


// Determines if the vote is valid (one of the candidates listed) and if so, stores the vote in ranks array for the voter
bool vote(int rank, string name, int ranks[])
{
    // Goes through each candidate to see if it matches the name inputed
    for (int i = 0; i < candidate_count; i++)
    {
        // If the names match, the vote is valid and we can store the candidate index into the ranks array for the voter
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // If the name the voter inputed is not one of the candidates names, the vote is invalid
    return false;
}


// Records the ranking list for each voter into the global paired preferences array (counts votes for 1 vs 1 candidates)
void record_preferences(int ranks[])
{
    // Compares each ranking 'i' to the rest of the rankings list 'j' in 1 vs 1 format (lower ranking than 'i')
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Adds a voter count to each preference where rank 'i' is preferred over rank 'j' (1 vs 1 vote)
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}


// Record pairs of candidates where one is preferred over the other (no tie) into the pairs array with a winner and loser (recorded as the candidate index)
// Also tallies up the number of valid pair counts (no tied pairs included)
void add_pairs(void)
{
    // Goes through each candidate 'i' and compares it to the rest of the candidates 'j' remaining (not already compared to avoid duplicates)
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // If there is a clear winner when one candidate has more votes than the other, they are added as a pair (records the winner and loser)
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory (strength is the difference between the number of 1 vs 1 votes between the pair)
// Selection sort is done in this case
void sort_pairs(void)
{
    // Define a buffer for the swapping
    pair buffer;

    // Goes through each pair at index 'i' and compares it to the rest of the pairs at index 'j' in a loop comparing the strengths
    for (int i = 0; i < pair_count; i++)
    {
        // Highest index initially set at 'i' so we can substitute it out
        // Strength is the difference between the number of 1 vs 1 votes between the pair
        int highestindex = i;
        int strength = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];

        // Compares the rest of the list of pairs to see what index contains the highest strength value
        for (int j = i + 1; j < pair_count; j++)
        {
            int nextstrength = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (nextstrength > strength)
            {
                highestindex = j;
                strength = nextstrength;
            }
        }
        // Once the highest index is determined, the pair at the highest index is swapped with the 'ith' index using the buffer
        buffer = pairs[i];
        pairs[i] = pairs[highestindex];
        pairs[highestindex] = buffer;

    }
    return;
}


// Lock pairs into the candidate graph in order (highest to lowest strengths), without creating cycles
void lock_pairs(void)
{
    // Goes through each of the pairs, in order of highest to lowest strength, to lock them in (as long as no cycles are created)
    for (int i = 0; i < pair_count; i++)
    {
        // Determines if a cycle could be created by locking in pair 'i' (looking at locked pairs created before)
        // If a cycle cannot be created, then it locks in that pair
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}


// Recursive function that determines if a cycle can be created if the pair of winners/losers is locked in
bool cycle(int winner, int loser)
{
    // Base case
    // If the loser has already won against the winner and it is locked, this is a direct cycle (returns true)
    if (locked[loser][winner] == true)
    {
        return true;
    }

    // Recursive case
    // If the loser has locked a win against another candidate 'i', and recursion determines 'i' will lock in a win again the winner, there is still a cycle
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] && cycle(winner, i))
        {
            return true;
        }
    }
    // If no cycles can occur, returns false
    return false;
}


// Print the winner of the election (winner has no locked arrows pointing at itself)
void print_winner(void)
{
    // Goes through each of the candidates 'i' and compares it to every other candidate 'j' to see if there is a locked arrow pointing at itself ('i')
    for (int i = 0; i < candidate_count; i++)
    {
        // x is initially set a 0 to indicate no locked arrows pointing at 'i'
        int x = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            // If there is a locked arrow pointing from candidate 'j' to 'i', then it is not the winner (x is incremented)
            if (locked[j][i] == true)
            x++;
        }

        // If candidate 'i' has no locked arrows pointing at itself, then it is the winner!
        if (x == 0)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
