// The 'candidate' program gets the user to input a list of presidential candidates' names and number of votes in an array and prints it back onto the screen
// Uses typedef struct to define our own data type of 'candidate' for the 'candidate_array' array that contains fields/attributes of names and votes

#include <cs50.h>
#include <stdio.h>

// Defines the size of the number of candidates array
#define SIZE 3

// Create a new data type called 'candidate' that groups together a name and number of votes
typedef struct
{
    string name;
    int votes;
}
candidate;

// Function prototypes
candidate get_candidate(string prompt);


int main(void)
{
    // Defined a new array with the newly created data type 'candidate' that stores names and number of votes
    candidate candidate_array[SIZE];

    // Gets user to input a name and number of votes for each candidate to store in the 'candidate_array'
    // 'candidate_array' has fields/attributes of names and votes for the data type
    for (int i = 0; i < SIZE; i++)
    {
        candidate_array[i] = get_candidate("Enter candidate: ");
    }

    for (int i = 0; i < SIZE; i++)
    {
        // Prints the candidate number in the list, name and number of votes
        printf("Candidate %i name: %s\n", i + 1, candidate_array[i].name);
        printf("Candidate %i votes:%i\n", i + 1, candidate_array[i].votes);
    }
}

// Function gets the user to input a name and number of votes for a candidate to store in the 'candidate_array'
// 'candidate_array' has fields/attributes of names and votes for the data type
candidate get_candidate(string prompt)
{
    // Prints the prompt to enter candidate information
    printf("%s\n", prompt);

    // Gets the user to input a name and number of votes for the candidate to store in a single variable with different fields/attributes
    candidate c;
    c.name = get_string("Enter a name: ");
    c.votes = get_int("Enter the number of votes: ");
    return c;
}
