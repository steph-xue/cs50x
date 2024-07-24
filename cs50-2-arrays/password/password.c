// The 'password' program allows the user to input a password
// It checks if the a password is valid (has at least one lowercase letter, uppercase letter, number and symbol)

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    // Gets the user to input a password
    string password = get_string("Enter your password: ");

    // Determines and prints if the password is valid (has at least one lowercase letter, uppercase letter, number and symbol) or invalid
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// Determines if the password is valid (has at least one lowercase letter, uppercase letter, number and symbol) or invalid
bool valid(string password)
{
    // Declaring all checks as false initially, so if the password passes each test we can declare each as true
    bool lowercase = false;
    bool uppercase = false;
    bool digit = false;
    bool symbol = false;

    // If there is a character in the password that passes each test, we can declare each test as true
    for (int i = 0, n = strlen(password); i < n; i++)
    {
        if (islower(password[i]))
        {
            lowercase = true;
        }
        if (isupper(password[i]))
        {
            uppercase = true;
        }
        if (isdigit(password[i]))
        {
            digit = true;
        }
        if (!isalnum(password[i]) && !isblank(password[i]))
        {
            symbol = true;
        }
    }

    // Returns the password as valid if it passes all of the tests and invalid otherwise
    if (lowercase && uppercase && digit && symbol)
    {
        return true;
    }
    else
    {
        return false;
    }
}
