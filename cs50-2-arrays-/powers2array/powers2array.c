// The "powers2array" program allows the user to input 'n' size of the array
// It prints out each element in the array where each subsequent element is double the previous one in the array

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Gets user to input a size for the array (>0)
    int n;
    do
    {
        n = get_int("What size of array? ");
    }
    while (n < 1);

    // Creating an array of 'n' size
    int array[n];

    // Assigns the 1st element of the array to 1 and printing it
    array[0] = 1;
    printf("%i\n", array[0]);

    // Assigns and prints each subsequent element in the array a number that is double the previous
    for (int i = 1; i < n; i++)
    {
        array[i] = array[i-1] * 2;
        printf("%i\n", array[i]);
    }
}
