// The 'volume' program allows the user to adjust the audio of a .wav file by a specific factor (e.g 2.0) and save it to a new file
// The user can input into the command-line: ./volume [input.wav] [output.wav] [factor]
    // Practicing using read/write file functions to copy the header over to a new file (represented by unsigned 8 bit/1 byte integers)
    // Practicing using read/write file functions to copy each audio sample (represented by signed 16 bit/2 byte integers) and modifying the volume by a factor

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Reminds the user if they don't have the correct command-line arguments for the input file, output file, and factor to modify the volume
    if (argc != 4)
    {
        printf("Usage: ./volume [input.wav] [output.wav] [factor]\n");
        return 1;
    }

    // Open input file to read (lets the user know if file cannot be found/opened)
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Open new output file to copy data into (lets the user know if file cannot be opened)
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Converts the factor inputed at the command-line to a float
    float factor = atof(argv[3]);

    // Copy header from input file to output file (using the header array)
    // The header is represented by 44 unsigned 8 bit/1 byte integers
    uint8_t header[HEADER_SIZE];
    fread(header, 1, HEADER_SIZE, input);
    fwrite(header, 1, HEADER_SIZE, output);

    // Read samples from input file and write updated data to output file (volume modified by the factor inputed by the user at the command-line)
    int16_t buffer;
    while (fread(&buffer, 2, 1, input) != 0)
    {
        buffer *= factor;
        fwrite(&buffer, 2, 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
