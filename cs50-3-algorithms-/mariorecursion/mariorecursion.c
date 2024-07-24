// The "mario" program prompts the user to specify the size of bricks and prints the bricks to the screen in a staircase format with 'n' size
// The program uses recursion instead of iteration of loops

#include <cs50.h>
#include <stdio.h>

void draw(int n);

int main (void)
{
    // Gets height of staircase of bricks from the user
    int height = get_int("What size of bricks?: ");

    // Prints out the staircase of bricks based on the height inputed using recursion
    draw(height);
}


// Prints out the staircase of bricks based on the height inputed using recursion
void draw(int n)
{
    // Base case stops the recursion loop from going back further into 0 and negative numbers
    if (n <= 0)
    {
        return;
    }

    // Recursion calls upon the same function but goes back further to n-1 to print out the smaller rows of the staircase
    draw(n - 1);

    // Prints out a row of bricks in the staircase based on n
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}
