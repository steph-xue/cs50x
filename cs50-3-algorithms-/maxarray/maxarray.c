// The 'maxarray' program gets the user to input the number of elements for an array and a value for each corresponding element (any negative/positive integer)
// The program then determines the maximum value out of all elements in the array

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    // Gets the user to input the number of elements for an array (at least 1 element)
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    // Declares an array of size 'n' inputed by the user
    int arr[n];

    // Gets the user to input an element (negative/positive integer value) to store in the array
    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    // Determines and prints out the maximum value out of all elements in the array
    printf("The max value is %i.\n", max(arr, n));
}


// Determines the maximum value out of all elements in the array
int max(int array[], int n)
{
    // Initial maximum value is set as the first element of the array, which we can then compare and replace as we go along
    int maxvalue = array[0];

    // Iterating through all the elements of the array
    for (int i = 0; i < n; i++)
    {
        // If any elements are larger than the maximum value, it becomes the new maximum value
        if (array[i] > maxvalue)
        {
            maxvalue = array[i];
        }
    }
    return maxvalue;
}
