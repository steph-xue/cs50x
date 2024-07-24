// The 'debugcreate' program is a debugging memory exercise to practice fixing memory issues that valgrind ./debugcreate [file name] generates
// The program takes the file name the user inputs as a command-line argument and then creates a new file for it
    // Shorter version

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for improper usage, otherwise, get filename length
    if (argc != 2)
    {
        printf("Wrong usage: Try ./create [filename]\n");
        return 1;
    }

    // Open new file under the name stored at filename
    FILE *new_file = fopen(argv[1], "w");

    // When opening a new program, we need to check to make sure we can actually open the program (points to correct memory to open)
    if (new_file == NULL)
    {
        printf("Cannot create file\n");
        return 1;
    }

    // Need to close the new file opened
    fclose(new_file);
}
