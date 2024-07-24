// The 'reverse' program takes an audio input.wav file and reverses the audio to the output.wav file
// The user can type in ./reverse [input.wav] [output.wav]
// The wav file header is 44 bytes and gives info about the file (type/size), and audio (channels, size per sample) to copy directly over
// Then each block of audio (# channels * bytes per sample) is copied over in reverse order

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

typedef uint8_t BYTE;

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure user inputs 2 command-line arguments
    if (argc != 3)
    {
        printf("Usage: ./reverse [input.wav] [output.wav]\n");
        return 1;
    }

    // Open input file for reading
    // Prints error message if file cannot be open (or found)
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Cannot open file %s\n", argv[1]);
        return 1;
    }

    // Read header
    // Populates the bytes of info into the different properties in the struct (in order) in the variable 'header'
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure the input file is in the correct WAV format
    if (check_format(header) == 0)
    {
        printf("Not a proper WAV file\n");
        return 1;
    }

    // Open output file for writing
    // Prints error message if file cannot be open
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Cannot open file %s\n", argv[1]);
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(header), 1, output);

    // Use get_block_size to calculate size of audio blocks
    int blocksize = get_block_size(header);

    // Write reversed audio to file
    // Buffer array (array of bytes) declared to copy over each block one at a time
    BYTE buffer[blocksize];

    // Puts pointer at the end of file offset by 1 block backwards
    fseek(input, - blocksize, SEEK_END);

    // Loop continues to copy audio blocks in reverse order until the header is reached (does not copy header again)
    while (ftell(input) >= sizeof(header))
    {
        // Reads and copies 1 block of audio at a time and then goes 2 blocks backwards
        fread(buffer, sizeof(BYTE), blocksize, input);
        fwrite(buffer, sizeof(BYTE), blocksize, output);
        fseek(input, -2 *(blocksize), SEEK_CUR);
    }

    // Closing the files
    fclose(input);
    fclose(output);
}


// Use check_format to ensure the input file is in the correct WAV format
// The file format in the header (bits 8-11) must spell out 'WAVE' (in integer format)
int check_format(WAVHEADER header)
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }
    return 0;
}


// Use get_block_size to calculate size of audio blocks
// Each block of audio is calculated by the number of channels times the bytes per sample (8 bits in a byte)
int get_block_size(WAVHEADER header)
{
    int size = header.numChannels * (header.bitsPerSample / 8);
    return size;
}
