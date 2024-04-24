// The 'caesar' program allows the user to input a number 'key' as an argument in the command-line and a 'plaintext' message they want to encrypt
// The program takes the message and rotates each alphabetical character by the key and prints out the encrypted message as 'ciphertext'
// Lowercase and uppercase letters stay in the same state, non-alphabetical characters remain unchanged

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string input);
char rotate(char c, int key);

int main(int argc, string argv[])
{
    // Program only takes 1 command-line argument 'key' and reminds the user if there is less/more than 1 command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Command-line argument 'key' should only be digits and reminds the user if there are non-digits
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Turn the command-line 'key' from a string to an integer
    int key = atoi(argv[1]);

    // Get user to input a plaintext message to encrypt
    string text = get_string("plaintext:  ");

    // Prints the heading for the cipher text
    printf("ciphertext: ");

    // Rotates and prints out each character in the plaintext message by using the integer key and Caesar's formula
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Rotates each character in the plaintext message to ciphertext
        text[i] = rotate(text[i], key);

        // Prints out the ciphertext character
        printf("%c",text[i]);
    }
    printf("\n");

}


// Determines if the characters in the command-line argument key are only digits
bool only_digits(string input)
{
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            return false;
        }
    }
    return true;
}


// Rotates each character in the plaintext message by the integer key using Caesar's formula
// Upper/lower case characters are left in the same case, and non-alpha characters are left as is
char rotate(char c, int key)
{
    // If the character is uppercase, it rotates it (converts to numerical value (0-25), adds key, makes sure value < 26, converts it back to character)
    if (c >= 'A' && c <= 'Z')
    {
        return ((c - 65 + key) % 26) + 65;
    }

    // If the character is lowercase, it rotates it (converts to numerical value (0-25), adds key, makes sure value < 26, converts it back to character)
    else if (c >= 'a' && c <= 'z')
    {
        return ((c - 97 + key) % 26) + 97;
    }
    
    // If the character is not a letter, it leaves it as is
    else
    {
        return c;
    }
}
