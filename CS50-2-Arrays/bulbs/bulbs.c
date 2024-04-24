// The 'bulbs' program allows the user to input a secret message
// The program prints out the secret message in binary code represented by on and off light bulbs

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Number of bits in a byte for each character
const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // Get code from the user
    string code = get_string("Message: ");

    // Go through each character in the text to determine the character's ASCII number, binary code, and then prints the binary code out in light bulbs
    for (int i = 0, n = strlen(code); i < n; i++)
    {
        // Turn the character in the text to an ASCII number
        int number = code[i];

        // Declare an array called bulbs
        int bulbs[BITS_IN_BYTE] = {0, 0, 0, 0, 0, 0, 0, 0};

        // Determine the binary code for the character (in zeros and ones) to store in the bulbs array
        for (int j = BITS_IN_BYTE - 1; j >= 0; j--)
        {
            bulbs[j] = number % 2;
            number = number / 2;
        }

        // Print out on/off bulbs for the binary code of each character stored in the bulbs array (single line for a character)
        for (int k = 0; k < BITS_IN_BYTE; k++)
        {
            // Prints out a on/off bulb for each individual zero/one in the binary code
            print_bulb(bulbs[k]);
        }
        printf("\n");
    }


}


// Prints out a on/off bulb for each individual zero/one in the binary code
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
