// The 'license' program takes license plates from plates.txt and prints them out to the screen
// Practicing debugging, allocating memory for strings, and pointer/string notation
    // Note: Ways to store array of characters for 1 string
        // char a[num of c]
        // char *a = malloc(num of c)
    // Note: Ways to store arrays for strings
        // char a[num of s][num of c] ** 2d array for static strings (must directly assign using char a[num of s] = "string")
        // char (*a)[num of s] **1d array for static strings (must directly assign using a[num of s] = "string")
        // char (*a) [num of c] = malloc(num of s * num of c) **Dynamic array for strings (can use strcpy)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Number of license plates
#define NUMPLATES 8

int main(int argc, char *argv[])
{
    // Check for 1 command-line inputed
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Open the input file (inputed by the user in the command-line argument)
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    // Create buffer to read a license plate into
    char buffer[7];

    // Create array of strings to store all plate numbers
    // Note notation below: to create array of strings, use malloc (for total memory), [size] where size is the number of characters in each string
    // Parentheses must be in place
        // char (*plates)[7] means a pointer to an array of strings each containing 7 characters
        // char *plates[7] means an array of 7 pointers
    char (*plates)[sizeof(buffer)] = malloc(sizeof(buffer) * NUMPLATES);
    if (plates == NULL)
    {
        return 1;
    }

    // Start the index at 0 to copy over all strings from buffer to plates array
    int idx = 0;

    // Loop occurs while there are still license plates in the plates.txt file
    // Reads license plates one at a time into the buffer array, and then stores them in the plates at each corresponding idx
    while (fread(buffer, sizeof(char), sizeof(buffer), infile) == sizeof(buffer))
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Save plate number in array
        strcpy(plates[idx], buffer);
        idx++;
    }

    // Print out each licence plate in the plates[] array
    for (int i = 0; i < NUMPLATES; i++)
    {
        printf("%s\n", plates[i]);
    }

    // Free space from malloc
    free(plates);
}
