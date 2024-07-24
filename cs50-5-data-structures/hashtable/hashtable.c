// The 'hashtable' program is to practice generating a hash function to produce a hash code (to make a hash table)
// It takes phrases from the user and then inputs each phrase into a hash function to produce a hash code
// The hash code must be an index to the array of pointers in the hash table [from 0 to n-1]

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creating a data type 'node' that contains a phrase and pointer to the next node (linked lists in hash table)
typedef struct node
{
    string phrase;
    struct node *next;
}
node;

// Creating an array of pointers for the hash table
node *table[26];

// Function prototypes
int hash(string phrase);

int main(void)
{
    // Getting a phrase from the user to input into the hash function to generate a hash code
    // The hash code must be an index to the array of pointers in the hash table [from 0 to n-1]
    for (int i = 0; i < 3; i++)
    {
        string phrase = get_string("Enter a new phrase: ");
        int index = hash(phrase);

        // Prints the phrase and hash code generated for visualization
        printf("%s hashes to %i\n", phrase, index);
    }
}

// Takes the phrase from the user into a hash function to generate a hash code
// The hash code must be an index to the array of pointers in the hash table [from 0 to n-1]
int hash(string phrase)
{
    return toupper(phrase[0]) - 'A';
}
