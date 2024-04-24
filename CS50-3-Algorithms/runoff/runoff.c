// The 'runoff' program gets the user to input the candidate names in a list as command-line arguments (max 9)
// It then prompts the user to input the number of voters (max 100), each person's ranking of votes (all candidates must be valid and listed at least once)
// If a candidate has won (>50% of of the top votes and not yet eliminated), then it prints out the name of the candidate who won
// If no candidates have won, it determines the lowest vote count and eliminates the candidate(s) with the lowest votes
// Then the cycle repeats again for the candidates left using the top voted candidates (disregarding the ones who have been now eliminated)
// If all candidates have tied at the lowest vote count, it prints out each of those candidate's names who have tied

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// 2 dimentional array that contains all the voters and their order of preferences for candidates
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

int main(int argc, string argv[])
{
    // Check for invalid usage (no candidates inputed)
    // Candidates should be listed as command-line arguments
    if (argc < 2)
    {
        printf("Usage: ./runoff [candidate 1] [candidate 2] [...]\n");
        return 1;
    }

    // Determine the number of candidates inputed
    candidate_count = argc - 1;

    // If number of candidates is greater than the max number, the program reminds the use of the max number of candidates
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    // Populates the candidate names into the candidate[] array, sets all the vote counts to zero, and sets if eliminated to false
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    // Gets the user to input the total number of people voting
    voter_count = get_int("Number of voters: ");
    printf("\n");

    // If the number of voters is greater than the max number, the program reminds the user of the max number of voters
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep asking for votes from each voter (from 1st to the last voter)
    for (int i = 0; i < voter_count; i++)
    {
        // Prints the voter number
        printf("Voter %i\n", i + 1);

        // Keep asking for list of rankings that includes all candidates (from 1 to the last ranking)
        for (int j = 0; j < candidate_count; j++)
        {
            // Gets the user to input the candidate rankings
            string name = get_string("Rank %i: ", j + 1);

            // Record ranking vote in the preferences array, unless it's invalid then it prints invalid vote to the screen
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists (continous loop)
    while (true)
    {
        // Calculates the number of top choice votes for each candidate not already eliminated
        tabulate();

        // Check if election has been won by a candidate that has not yet been eliminated (if one candidate has >50% of the top choice votes)
        // If election is won, the winner is printed and the program is finished running
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Determine the minimum number of votes and see if there is a tie between every candidate left
        int min = find_min();
        bool tie = is_tie(min);

        // If tie between every candidate left, everyone who is left wins (prints the tie winners and program is finished running)
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("Tie: %s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes (if no tie occurs)
        eliminate(min);

        // Reset vote counts back to zero (top choice votes for each candidate)
        // The loop is then restarted to calculate the vote count for the candidates that are left
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}


// Record ranking vote in the preferences array if valid vote, or determines if it is an invalid vote
bool vote(int voter, int rank, string name)
{
    // Goes through each candidate name
    for (int i = 0; i < candidate_count; i++)
    {
        // If the name the voter ranked is a valid candidate, it stores that candidate number into the preferences array and returns valid
        // The preferences array records the voter #, rank #, and candidate # to record an array of the voter's preferences
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }

    // If the name the voter ranked is not a valid candidate, it returns invalid
    return false;
}


// Calculates the number of top choice votes for each candidate not already eliminated
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}


// Check if election has been won by a candidate that has not yet been eliminated (if one candidate has >50% of the top choice votes)
// If election is won, the winner is printed and the function returns true, if not won the function returns false
bool print_winner(void)
{
    // Goes through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Candidate must not be eliminated and their number of votes must be >50% of the total number of votes to be a winner
        if (!candidates[i].eliminated && (candidates[i].votes > (voter_count/2)))
        {
            // If the candidate is determined a winner, it prints the name of the winner and returns true
            printf("Winner: %s!\n", candidates[i].name);
            return true;
        }
    }

    // If no winner is determined, it returns false
    return false;
}


// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Set the initial minimum vote as the total number of votes so we can compare and substitute the value out as we go along
    int minimumvote = voter_count;

    // Goes through each candidate and updates the minimum vote based on the smallest number of votes of a candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Candidate must not be eliminated to be accounted for when determining the minimum vote
        if (!candidates[i].eliminated && candidates[i].votes < minimumvote)
        {
            minimumvote = candidates[i].votes;
        }
    }
    return minimumvote;
}


// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Defining counts for the number of candidates with votes at the minimum vote (and will tie), and the number of candidates left (not eliminated)
    int tiecount = 0;
    int candidatesleft = 0;

    // Goes through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Adds a count to the number of candidates that have tied with the minimum vote who are not eliminated
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            tiecount++;
        }

        // Adds a count to the total number of candidates left (not eliminated)
        if (!candidates[i].eliminated)
        {
            candidatesleft++;
        }
    }

    // If the number of candidates tied to the minimum vote is equal to the total number of candidates left, it is considered a tie
    if (tiecount == candidatesleft)
    {
        return true;
    }

    // If not all candidates have a vote that is equal to the minimum vote, it is not a tie
    return false;
}


// Eliminate the candidate(s) in last place (if no tie occurs)
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
