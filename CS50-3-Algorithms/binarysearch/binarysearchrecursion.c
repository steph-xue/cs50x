// The 'binarysearchrecursion' program gets the user to input a number they want to search for in an already predetermined and sorted array
// It uses binary search (recurison version) to see if the target number is in the array, and prints if it is found or not found

#include <cs50.h>
#include <stdio.h>

bool binarysearch(int a[], int n, int l, int r);

int main(void)
{
    // Declares an array with sorted numbers in ascending order
    int size = 10;
    int array[] = {1, 3, 4, 6, 7, 9, 11, 13, 14, 16};

    // Gets the user to input a number to search for in the array
    int target = get_int("What number do you want to search for?: ");

    // Uses binary search (recursion version) to search for the target number
    // Prints if found or not found in the array
    if (binarysearch(array, target, 0, size - 1))
    {
         printf("Found!\n");
    }
    else
    {
        printf("Not found!\n");
    }
}


// Uses binary search (recursion version) to search for the target number
bool binarysearch(int a[], int n, int l, int r)
{
    // Base case
    // If left bound is greater than the right bound and the number hasn't been found, it is not in the array
    if (l > r)
    {
        return false;
    }

    //Recursive case
    // Calculating the mid point for each recursion
    int mid = (l + r) / 2;

    // Searches to see if the target number is in the middle, or searches to the left/right depending on if the target number is less/greater than the middle
    // The left and right bounds change accordingly with each recursion depending on which section of the array we are looking at
    if (n == a[mid])
    {
        return true;
    }
    else if (n < a[mid])
    {
        return binarysearch(a, n, l, mid - 1);
    }
    else
    {
        return binarysearch(a, n, mid + 1, r);
    }
}
