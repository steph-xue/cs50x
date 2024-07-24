// The 'linearsearch' program implements a linear search algorithm to find a number 'n' inputed by the user in an already defined array of numbers

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Defines the size of the array and the numbers stored in the array
    int size = 7;
    int numbers[] = {20, 500, 10, 5, 100, 1, 50};

    // Gets the user to input a number 'n' to find in the already defined array
    int n = get_int("Number: ");

    // Implements a linear search algorithm to search the array numbers[] from left to right to find the number 'n' specified by the user
    for (int i = 0; i < size; i++)
    {
        if (numbers[i] == n)
        {
            printf("Found!\n");
            return 0;
        }
    }
    printf("Not found!\n");
    return 1;

}
