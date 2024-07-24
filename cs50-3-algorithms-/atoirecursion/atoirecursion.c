// The 'atoi' program gets the user to input a postive integer and stores it as a string
// It turns the string to an actual integer and prints it out onto the screen using recursion instead of the atoi() function

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    // Gets the user to input a positive integer to store into a string
    string input = get_string("Enter a positive integer: ");

    // If any of the characters in the string inputed is not a number, it tells the user the input is invalid (all characters must be numbers)
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Converts string to int using recursion and prints the int number back onto the screen
    printf("%i\n", convert(input));
}


// Converts string to int using recursion
int convert(string input)
{
    // Base case
    // If there are no more characters in the string, the last step of the convert() recursion gives a zero value
    if (strlen(input) == 0)
    {
        return 0;
    }

    // Recursive case
    // The last character of the string is turned into an integer using ASCII codes and stored in 'n'
    int n = input[strlen(input) - 1] - '0';

    // The last character of the string is then turned into a null character to remove the last character
    input[strlen(input) - 1] = '\0';

    // The function returns the last digit integer added to a product of 10 times the recursive function convert(input with 1 less character)
    return n + 10 * convert(input);
}
