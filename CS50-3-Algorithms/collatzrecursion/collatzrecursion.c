// THe 'collatzrecursion' program gets the user to input a number, and then uses the Collatz conjecture to determine the number of steps to reach 1
// Uses a recursion function

#include <cs50.h>
#include <stdio.h>

int collatz(int n);

int main(void)
{
    // Gets the user to input a number for the Collatz conjecture
    int number = get_int("What number?: ");

    // Using the Collatz conjecture recursion function, determines the number of steps to reach 1
    int steps = collatz(number);

    // Prints the number of steps to perform the Collatz conjecture to get 1
    printf("Number of steps: %i\n", steps);

}


// Using the Collatz conjecture recursion function, determines the number of steps to reach 1
int collatz(int n)
{
    // Base case: if n == 1, there are no extra steps to be taken
    if (n == 1)
    {
        return 0;
    }

    // Even recursive case adds 1 step
    else if ((n % 2) == 0)
    {
        return 1 + collatz(n / 2);
    }

    // Odd recursive case adds 1 step
    else
    {
        return 1 + collatz((3 * n) + 1);
    }
}
