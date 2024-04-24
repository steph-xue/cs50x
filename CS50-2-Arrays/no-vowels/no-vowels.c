// The 'no-vowels' program gets the user to input a command-line argument word and substitutes all the vowels with similar looking numbers

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string replace(string word);

int main(int argc, string argv[])
{
    // Reminds the user if they have more or less than 1 command-line argument word
    if (argc != 2)
    {
        printf("./no-vowels word\n");
        return 1;
    }

    // Replaces the vowels in the command-line argument word with similar looking numbers
    string output = replace(argv[1]);

    // Prints the word with vowels substituted with similar looking numbers
    printf("%s\n", output);
}


// Replaces the vowels in the command-line argument word with similar looking numbers
string replace(string word)
{
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        switch (tolower(word[i]))
        {
            case 'a':
                word[i] = '6';
                break;

            case 'e':
                word[i] = '3';
                break;

            case 'i':
                word[i] = '1';
                break;

            case 'o':
                word[i] = '0';
                break;

            default:
                break;
        }
    }
    return word;
}
