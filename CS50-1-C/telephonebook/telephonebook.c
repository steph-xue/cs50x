// The "telephonebook" program prompts the user to input their name, age, and phone number and prints them all in a telephone book format

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Gets the user to input their name, age, and phone number (phone number can include spaces and hyphens)
    string name = get_string("What is your name?: ");
    int age = get_int("What is your age?: ");
    string phone = get_string("What is your phone number?: ");

    // Prints the inputed name, age, and phone number all in a telephone book format
    printf("Name: %s\n", name);
    printf("Age: %i\n", age);
    printf("Phone number: %s\n", phone);
}
