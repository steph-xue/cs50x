// The 'plurality' program allows the user to input the candidate names in a list as command-line arguments
// It then prompts the user to input the number of voters, each person's vote, and then it prints out the names of the candidates who have won
// If there are more than one candidates who have tied, it prints out each of those candidate's names

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
    // Check for invalid usage (no candidates inputed)
    // Candidates should be listed as command-line arguments
    if (argc < 2)
    {
        printf("Usage: ./plurality [candidate 1] [candidate 2] [...]\n");
        return 1;
    }

    // Determine the number of candidates inputed
    candidate_count = argc - 1;

    // If number of candidates is greater than the max number, the program reminds the use of the max number of candidates
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // Populates the candidate names into the candidate[] array and sets all the vote counts to zero
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    // Gets the user to input the total number of people voting
    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        // Every voter inputs a candidate's name
        string name = get_string("Vote: ");

        // If the voter's inputed name is not one of the candidates, it prints out that it is an invalid vote
        // The vote() function also adds up the number of votes for each candidate in the candidate[] array
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Prints out the winner of election (based on the number of votes)
    print_winner();
}


// If the voter's inputed name is not one of the candidates, it prints out that it is an invalid vote
// The vote() function also adds up the number of votes for each candidate in the candidate[] array
bool vote(string name)
{
    // Checking the voter's inputed name against each of the candidate's names (in the candidate array)
    for (int i = 0; i < candidate_count; i++)
    {
        // If the voter's inputed name matches a candidate's name, increases the vote count for that candidate by 1 and returns the vote as valid (true)
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    // If the voter's inputed name does not matches a candidate's name, it returns the vote as invalid (false)
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Highest vote number is initially set to zero
    int highestvote = 0;

    // Goes through each of the candidates and their votes to determine what the highest vote number is
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > highestvote)
        {
            highestvote = candidates[i].votes;
        }
    }

    // Prints out each of the candidates names who have a vote number equivalent to the highest vote number
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == highestvote)
        {
            printf("%s wins!\n", candidates[j].name);
        }
    }
    return;
}
