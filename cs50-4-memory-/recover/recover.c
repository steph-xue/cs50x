// The 'recover' program recovers the lost jpeg images that were deleted from the camera and are now stored in the card.raw memory card file
// The user can type in ./recover [card.raw] to extract all lost jpeg files into seperate image files to recover them

// The memory card uses the FAT file system that separates memory into blocks of 512 bytes, and each start of the jpeg is aligned with the blocks
// Jpeg files may span a number of blocks, and the end of the jpeg file may not align with the end of the block (slack is filled with zeros)
// Jpeg files have a signature 4 byte header '0xff 0xd8 0xff' and '(0xe0 - 0xef)' that allows you to locate the start of a jpeg image
// The signature can be used to separate the jpeg files out from one another and extract them into separate files

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Each block of the memory card contains 512 bytes
#define BLOCKSIZE 512

// Defining a byte as an unsigned 8 bit integer
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check that the user provided only 1 command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover [card.raw]\n");
        return 1;
    }

    // Open memory card file (card.raw) for reading
    FILE *input = fopen(argv[1], "r");

    // Check if the file can be opened (valid file name inputed)
    if (input == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    // Set counter for the number of jpgs generated to 0
    int jpgcounter = 0;

    // Dynamic memory allocation for the file name
    // '000.jpg\0' gives 8 characters = 8 bytes)
    char *filename = malloc(8);

    // Check if the filename is not pointing to memory space (to avoid crashes)
    if (filename == NULL)
    {
        return 1;
    }

    // Create pointer for the output files that will be created
    FILE *output = NULL;

    // Create a buffer array to store each byte in an element for every block read
    BYTE buffer[BLOCKSIZE];

    // Read 512 bytes into a buffer and repeat until end of card (returns 0 if nothing is read signifying the end of the memory card)
    while (fread(buffer, 1, BLOCKSIZE, input) == BLOCKSIZE)
    {
        // If start of new JPEG (based on '0xff 0xd8 0xff' and '(0xe0 - 0xef)' 4 byte signature)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If not the first JPEG only (close the last jpeg file)
            if (jpgcounter != 0)
            {
                fclose(output);
            }

            // Create a new file name and open a new file for the jpeg image
            sprintf(filename, "%03i.jpg", jpgcounter);
            output = fopen(filename, "w");

            // Lets the user know if the file cannot be opened
            if (output == NULL)
            {
                printf("Cannot open file\n");
                return 1;
            }

            // Adds up the number of jpeg images found
            jpgcounter++;
        }
        // For each block (after the first jpeg has been found), write the block contents into the jpeg file
        if (jpgcounter != 0)
        {
        fwrite(buffer, 1, BLOCKSIZE, output);
        }
    }

    // Close the output file
    fclose(output);

    // Close the input file
    fclose(input);

    // Free the malloc for the file name
    free(filename);

    return 0;
}
