// The 'pdf' program gets the user to input a file as a command-line argument and lets the user know if it is likely a pdf file or not
// pdf files characteristically start with 4 uint8_t numbers (37, 80, 68, 70)
// We can open the file inputed and check to see if the first several numbers match and if they do, the file is likely a pdf
    **//Note files were not provided so the program doesn't actually run

#include <cs50.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // If less or more than 1 command-line argument, it reminds the user to only input 1 file name into the command-line
    if (argc != 2)
    {
        printf("Usage: ./pdf.c [file name]\n");
        return 1;
    }

    // Open file using the file name inputed into the command-line
    char *filename = argv[1];
    FILE *ptr = fopen(filename, "r");

    // Check if file exits
    if (ptr == NULL)
    {
        printf("No such file found\n");
        return 1;
    }

    // Creates a buffer to store the first 4 uint8_t numbers that signifies the file type (pdf = 37, 80, 68, 70)
    uint8_t buffer[4];

    // Creates an array to store the actual numbers representing the beginning of a pdf
    uint8_t pdf[] = {37, 80, 68, 70};

    // Reads into the file opened and stores the first 4 uint8_t numbers into the buffer array
    fread(buffer, 1, 4, ptr);

    // Compares the buffer stored uint8_t numbers against the actual real pdf numbers to see if the file is a pdf
    for (int i = 0; i < 4; i++)
    {
        if (buffer[i] != pdf[i])
        {
            printf("Likely not a pdf\n");

            // Close the file before ending the program
            fclose(ptr);
            return 0;
        }
    }
    printf("Likely a pdf\n");

    // Close the file before ending the program
    fclose(ptr);
    return 0;



}
