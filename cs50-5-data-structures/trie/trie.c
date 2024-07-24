// The 'trie' program saves a list of the top 150 popular dog names in a trie
// The user can type in ./trie [dog_names.txt] and then input a dog name to check if it is a top 150 dog name (name is in the trie)
    // Check function needs to be implemented to check the user inputed dog name against the dog names stored in the trie

// List of the top 150 popular dog names found in:
// https://www.dailypaws.com/dogs-puppies/dog-names/common-dog-names

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions for size of alphabet (node array) and max number of characters for the dog name
#define SIZE_OF_ALPHABET 26
#define MAXCHAR 20

// Each node will contain a bool to check if the end of word is reached
// Also contains an array of pointers to children based on the letter of the alphabet in the word
typedef struct node
{
    bool is_word;
    struct node *children[SIZE_OF_ALPHABET];
}
node;

// Function prototypes
bool check(char *word);
bool unload(void);
void unloader(node *current);

// Root of trie
node *root;

// Buffer to read dog names into
char name[MAXCHAR];

int main(int argc, char *argv[])
{
    // Check user has only inputed 1 command-line argument
    if (argc != 2)
    {
        printf("Usage: ./trie [infile]\n");
        return 1;
    }

    // Open file with dog names and print out error if unable to open
    FILE *infile = fopen(argv[1], "r");
    if (!infile)
    {
        printf("Error opening file!\n");
        return 1;
    }

    // Allocate memory for node at root of trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        printf("Not enough memory to allocate node\n");
        return 1;
    }

    // Set the node at the root of trie to false and NULL for all pointers
    root->is_word = false;
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        root->children[i] = NULL;
    }

    // Add words one at a time to the trie from the dog names file
    while (fscanf(infile, "%s", name) == 1)
    {
        // Point a temporary cursor at the root of the trie
        node *cursor = root;

        // Iterate through each character in the word, determining the ASCII index converted to an index between 0 and 25 (alphabet)
        for (int i = 0, n = strlen(name); i < n; i++)
        {
            int index = tolower(name[i]) - 'a';

            // If the pointer is NULL at the alphabet index, add a new node for that alphabetical character
            if (cursor->children[index] == NULL)
            {
                // Make node and set it to false, and all of its pointers to NULL
                // Connect the parent node to the new node
                node *new = malloc(sizeof(node));
                new->is_word = false;
                for (int j = 0; j < SIZE_OF_ALPHABET; j++)
                {
                    new->children[j] = NULL;
                }
                cursor->children[index] = new;
            }

            // Go to node which we may have just been made and repeat the process for all the rest of the characters in the word
            cursor = cursor->children[index];
        }

        // If we are at the end of the word (went through and allocated nodes for all characters), mark the last node as being a word (true)
        cursor->is_word = true;
    }

    // Gets the user to input a dog name of choice and checks if it has been found in the trie using the check() function
    if (check(get_string("Check word: ")))
    {
        printf("Found!\n");
    }
    else
    {
        printf("Not Found.\n");
    }

    // Unload the memory allocated with malloc when creating the nodes
    // Print error message if unable to unload
    if (!unload())
    {
        printf("Problem freeing memory!\n");
        fclose(infile);
        return 1;
    }

    // Close the dog names file
    fclose(infile);
}

// Checks if the dog name the user inputed has been found in the trie (is a top 150 dog name)
// Returns true if found, false if not found
bool check(char *word)
{
    // Point a temporary cursor at the root of the trie
    node *cursor = root;

    // Iterate through each character of the user inputed dog name
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Convert the character to the ASCII index converted to an index between 0 and 25 (alphabet)
        int index = tolower(word[i]) - 'a';

        // If the character node exists, move to the next node
        // If it doesn't exist, the word is not in the trie (returns false)
        if (cursor->children[index] != NULL)
        {
            cursor = cursor->children[index];
        }
        else
        {
            return false;
        }

        // If the last character has been reached and it is determined that the word is in the trie, return true
        if ((cursor->is_word == true) && (i == strlen(word) - 1))
        {
            return true;
        }
    }
    return false;
}

// Unload trie from memory
bool unload(void)
{

    // The recursive function handles all of the freeing
    unloader(root);

    return true;
}

void unloader(node *current)
{

    // Iterate over all the children to see if they point to anything and go there if they do point
    for (int i = 0; i < SIZE_OF_ALPHABET; i++)
    {
        if (current->children[i] != NULL)
        {
            unloader(current->children[i]);
        }
    }

    // After we check all the children point to null we can get rid of the node and return to the previous iteration of this function.
    free(current);
}
