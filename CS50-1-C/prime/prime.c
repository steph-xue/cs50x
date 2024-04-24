// The "prime" program prompts the user gives a minimum (> 0) and maximum range, and outputs a list of all prime numbers in the range

#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    // Get the user to input a minimum number that is greater than zero
    int min;
    do
    {
        min = get_int("Minimum (> 0): ");
    }
    while (min < 1);

    // Get the user to input a maximum number that is greater than the minimum
    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (max <= min);

    // Goes through each number in the range and prints the number out if it is a prime number
    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}


// Determines if the number is a prime number (only divisible by iself and 1, excluding the number 1 itself)
bool prime(int number)
{
    // If the number itself is 1, it is not a prime number
    if (number == 1)
    {
        return false;
    }

    // If the number is divisible by 2 up to the number minus 1, then it is not a prime number
    for (int i = 2; i < number; i++)
    {
        if ((number % i) == 0)
        {
            return false;
        }
    }
    return true;
}
