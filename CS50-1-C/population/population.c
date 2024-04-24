// The "population" program allows the user to input a starting number of llamas (>= 9) and goal number of llamas (>= starting number)
// It calculates the number of integer years to reach the goal number of llamas assuming 1/3 growth and 1/4 deaths each year

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Gets the user to imput the starting number of llamas (>=9)
    int start;
    do
    {
        start = get_int("Starting number of llamas (>=9): ");
    }
    while (start < 9);

    // Gets the user to imput the goal number of llamas (>=starting number)
    int goal;
    do
    {
        goal = get_int("Goal number of llamas (>= starting): ");
    }
    while (goal < start);

    // Determines the integer number of years to reach the goal number of llamas assuming 1/3 growth and 1/4 deaths each year
    int years = 0;
    while (start < goal)
    {
        start = start + (start/3) - (start/4);
        years++;
    }

    // Prints the integer number of years to reach the goal number of llamas onto the screen
    printf("Years: %i\n", years);
}
