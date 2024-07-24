// The "hello" program allows the user to input their first and last name, and prints out saying hello to the user with their first and last name

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get the user to input their first and last name
    string first = get_string("What is your first name?: ");
    string last = get_string("What is your last name?: ");

    // Prints hello with the first and last name
    printf("Hello, %s %s! \n", first, last);
}
