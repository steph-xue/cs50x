// The goal of speller is to write these functions (integrated in speller.c) to implement a dictionary's functionality to spell check a text file
// The spell checker should be as efficient as possible
    // load() function: loads dictionary into memory (in the form of a hash table with linked lists), returning true if successful, else false
    // hash() function: Hashes word to obtain a hash value (index for the hash table array used by both load() and check())
    // check() function: Spell checks each word from the text file with the loaded dictionary in the hash table
            // Returns true if word is in dictionary, else false
    // size() function: Returns number of words in dictionary if loaded, else 0 if not yet loaded
    // unload() function: Unloads dictionary (hash table nodes) from memory, returning true if successful, else false

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000000;

// Hash table
node *table[N];

// Number of words in the dictionary
int dictionarysize = 0;


// Loads dictionary into memory (hash table), returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    // If cannot open file, return false (error occurred)
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        printf("Cannot open dictionary file\n");
        return false;
    }

    // Set all pointers in the hash table to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Read words (strings) from dictionary file one at a time
    char stringword[LENGTH + 1];
    while (fscanf(input, "%s", stringword) != EOF)
    {
        // Create a new node for each word
        // If no more memory, return false (error occurred)
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Not enough memory to allocate another node\n");
            unload();
            fclose(input);
            return false;
        }

        // Input the word into the node
        strcpy(n->word, stringword);

        // Hash word to obtain a hash value
        unsigned int index = hash(stringword);

        // Insert node into hash table at that location
        n->next = table[index];
        table[index] = n;

        // Increment number of words in the dictionary loaded
        dictionarysize++;
    }

    // Close file
    fclose(input);

    return true;
}


// Hashes word to obtain a hash value (index for the hash table array)
unsigned int hash(const char *word)
{
    // Sum of the ACSII numbers (multiplied by 3333) of all the characters in the word, modulo the number of pointers in the hash table array
    // Characters to lowercase for consistency with dictionary words (same words get matched to same index)
    int x = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        x = x + tolower(word[i]) * 3333;
    }
    return x % N;
}


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Put word from the text through the hash function to obtain the hash value (index for hash function array)
    unsigned int index = hash(word);

    // Set pointer to point to the first node of the hash table at the determined index
    // Until the pointer reaches NULL (no more nodes in the current linked list), compare the word at each node with the text word
    // If the text word matches a word from the dictionary in the linked list, return true (word is in the dictionary), otherwise return false
    node *ptr = table[index];
    while (ptr != NULL)
    {
        if (strcasecmp(word, ptr->word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionarysize;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }

        // Return true if successfully reached the last node of the last linked list
        if (ptr == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
