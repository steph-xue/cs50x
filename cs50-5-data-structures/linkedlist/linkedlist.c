// The 'linkedlist' program practices creating a linked list
// The user can input a list of integer values as command-line arguments: ./linkedlist [n1] [n2] [...]
// The program will then print out that list (in reverse order as it is a stack not a queue)

#include <stdio.h>
#include <stdlib.h>

// Define a structure for the node (including the value it stores & pointer to link it to the next node)
typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(int argc, char *argv[])
{
    // Set the list pointer initially to point to NULL
    node *list = NULL;

    // Iterate through each command-line argument values inputed
    for (int i = 1; i < argc; i++)
    {
        // Converts the command-line arguments from a string to an integer
        int number = atoi(argv[i]);

        // Allocating memory to create a node (exits if no more memory left)
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }

        // Assigns values to the node and a pointer so it can point to the next node
        // Assign current node to point to the list (which points at NULL or previous node), then set list to point at current node (to created links)
        n->number = number;
        n->next = list;
        list = n;
    }

    // Create new pointer ptr to start at the list (beginning node)
    // While the pointer doesn't point to NULL (end of the nodes), continue print node's number and continue to print the next node
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }

    // Set pointer ptr to start at the list (beginning node again)
    // While the pointer doesn't point to NULL (end of the nodes), free up the memory at each node the ptr is pointing at
    // Next node pointer must be set beforehand to point at the next node, or else freeing ptr will result in memory loss/loss of next node
    ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}
