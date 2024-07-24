// The 'linkedlist' program is to practice generating linked lists
// The user can input a number of strings (based on LIST_SIZE)
// It it will store the string into a linked list and print out the location, phrase, and next location for each node for each string

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creating a data type 'node' that contains a phrase and pointer to the next node (linked list)
typedef struct node
{
    string phrase;
    struct node *next;
}
node;

// Defines the number of phrases the user can input
#define LIST_SIZE 2

// Function prototypes
void unload(node *list);
void visualize(node *list);

int main(void)
{
    // Setting the pointer to the list to first point at NULL
    node *list = NULL;

    // Add phrases to the linked list
    for (int i = 0; i < LIST_SIZE; i++)
    {
        // Gets the user to input a phrase
        string phrase = get_string("Enter a new phrase: ");

        // Add phrase to new node in list
        // Generating space for a new node, printing error if not enough memory, entering the phrase in the new node
        // Then linking the new node to the previous node (or NULL if first node), and pointing the head of the list back to the new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Couldn't allocate memory for node\n");
            return 1;
        }
        n->phrase = phrase;
        n->next = list;
        list = n;

        // Visualize (print) the linked list after adding a new node
        visualize(list);
    }

    // Free all the memory allocated for the nodes generated
    unload(list);
}


// Free all the memory allocated for the nodes generated
void unload(node *list)
{
    // Creates a pointer to point to the next node, frees the current node, and then moves on to the next node (until NULL is reached)
    node *ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}



// Visualize (print) the linked list after adding a new node
// Prints the location, phrase, and next location for each node for each string
    // List pointer starts at the head of the list, then points to the next node, etc. in a loop until NULL is reached
void visualize(node *list)
{
    printf("\n+-- List Visualizer --+\n\n");
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("Location %p\n", ptr);
        printf("Phrase: \"%s\"\n", ptr->phrase);
        printf("Next: %p\n\n", ptr->next);
        ptr = ptr->next;
    }
    printf("+---------------------+\n\n");
}
