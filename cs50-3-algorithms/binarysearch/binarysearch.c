// The 'binarysearch' program gets the user to input a number they want to search for in an already predetermined and sorted array
// It uses binary search (iteration version) to see if the target number is in the array, and prints if it is found or not found

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

    // Uses binary search (iteration version) to search for the target number
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


// Uses binary search (iteration version) to search for the target number
bool binarysearch(int a[], int n, int l, int r)
{
    // Loop runs to search smaller sections of the array as long as there are elements left to search through (left and right bounds do no cross over)
    while (l <= r)
    {
        // Calculating the mid point for each loop
        int mid = (l + r) / 2;

        // Searches to see if the target is in the middle, or searches to the left/right if the target number is less/greater than the middle
        // The left and right bounds change accordingly with each loop depending on which section of the array we are looking at
        if (n == a[mid])
        {
            return true;
        }
        else if (n < a[mid])
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    // If there are no elements left to search through (left and right bounds do no cross over), the number is not in the array
    return false;

}
