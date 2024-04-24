// The 'substitution' program allows users to input a 26-letter alphabet 'key' as a command-line argument and a 'plaintext' message they want to encrypt
// The program takes the message and substitutes each letter by the 26-letter alphabet key and prints out the encrypted message as 'ciphertext'
// The 26-letter alphabet 'key' can be in uppercase or lowercase, but must be valid (26 characters, only letters, no duplicate letters)
// Lowercase and uppercase letters stay in the same state, non-alphabetical characters remain unchanged

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool validnumber(string key);
bool validalpha(string key);
bool validnodouble(string key);
char substitute(char c, string key);

int main(int argc, string argv[])
{
    // Reminds the user if is is less or more than 1 the command-line argument key
    if (argc != 2)
    {
        printf("./substitution key\n");
        return 1;
    }

    // Determines if the command-line argument key is valid and only contains 26 characters
    if (!validnumber(argv[1]))
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    // Determines if the command-line argument key is valid and only contains alphabetical characters
    if (!validalpha(argv[1]))
    {
        printf("Key must contain only alphabetic characters\n");
        return 1;
    }

    // Determines if the command-line argument key is valid and does not contain double characters
    if (!validnodouble(argv[1]))
    {
        printf("Key must not contain double characters\n");
        return 1;
    }

    // Gets user to input text to encrypt
    string text = get_string("plaintext: ");

    // Prints the header for the ciphertext
    printf("ciphertext: ");

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        text[i] = substitute(text[i], argv[1]);
        printf("%c", text[i]);
    }
    printf("\n");
}


// Determines if the command-line argument key is valid and only contains 26 characters
bool validnumber(string key)
{
    if (strlen(key) == 26)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// Determines if the command-line argument key is valid and only contains alphabetical characters
bool validalpha(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
    }
    return true;
}


// Determines if the command-line argument key is valid and does not contain double characters
bool validnodouble(string key)
{
    for (int i = 0, n = strlen(key); i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (key[j] == key[i])
            {
                return false;
            }
        }
    }
    return true;
}


char substitute(char c, string key)
{
    if (isupper(c))
    {
        int number = c - 65;
        c = toupper(key[number]);
        return c;
    }
    else if (islower(c))
    {
        int number = c - 97;
        c = tolower(key[number]);
        return c;
    }
    else
    {
        return c;
    }
}
