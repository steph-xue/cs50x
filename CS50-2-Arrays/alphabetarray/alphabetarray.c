// The 'alphabetaarray' program allows the user to input a word (in lowercase) and determines if all letters are in alphabetical order

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Gets the user to input a word (in lowercase)
    string word = get_string("What word? (in lowercase): ");

    //Determines if all letters in the word are in alphabetical order
    for (int i = 0, n = strlen(word); i < n - 1; i++)
    {
        if (word[i] > word[i + 1])
        {
            printf("No, not all letters are in alphabetical order\n");
            return 0;
        }
    }
    printf("Yes, all letters are in alphabetical order\n");
    return 0;
}
