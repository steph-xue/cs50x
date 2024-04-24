// The 'realloc' program is just to practice using realloc from the stdlib.h library
// Realloc allows you to reallocate previous data to a new memory location with a bigger/smaller size

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // First creating a list of 3 integers using malloc
    // Gives an error if there is no memory left to allocate space
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }

    // Assigning values to the list
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // Reallocating the data in the list to a new location of memory of a bigger size to add an integer (called temp)
    // Reallocating automatically frees up the previous malloc
    // However in case of no memory to realloc, then the previous malloc must be manually freed before exiting the program
    int *temp = realloc(list, 4 * sizeof(int));
    if (temp == NULL)
    {
        free(list);
        return 1;
    }

    // We can rename the temp to the list again (previous list memory was freed)
    list = temp;

    // Add a new integer into the additional space
    list[3] = 4;

    // Prints out the values in the list (with the added 4th value)
    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    // Frees up the list before exiting the program
    free(list);
}
