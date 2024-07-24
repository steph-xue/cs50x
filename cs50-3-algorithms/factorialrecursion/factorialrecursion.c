#include <cs50.h>
#include <stdio.h>

int fact(int n);

int main(void)
{
    // Get the user to input a number to find the factorial for
    int number = get_int("What number to find the factorial for: ");

    // Function determines the factorial of the number using recursion
    int factorial = fact(number);

    printf("Factorial %i! is %i\n", number, factorial);


}


// Function determines the factorial of the number using recursion
int fact(int n)
{
    // Base case: factorial of 1 always returns 1 (terminates the recursion)
    if (n == 1)
    {
        return 1;
    }

    // Recursive case: calls upon the factorial function again
    else
    {
        return n * fact(n-1);
    }
}
