// The 'tempsbubblesort' program takes an array that contains a list of cities and their average highest July temps (element contains name of city and temp)
// The array is unsorted, and the program uses the bubble sorting algorithm to sort the elements from highest to lowest July temperatures
    // Practice working with structs
    // Practice applying bubble sorting algorithm

#include <cs50.h>
#include <stdio.h>

// Defines the total number of cities
#define NUM_CITIES 10

// Defines the data type avg_temp as containing both the city name and the average highest July temp
typedef struct
{
    string city;
    int temp;
}
avg_temp;

// Creates an array to store the city names and average highest July temps
avg_temp temps[NUM_CITIES];

// Function prototypes
void sort_cities(void);

int main(void)
{
    // Lists all the elements of the unsorted array, each element containing a city and its average highest July temp
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    // Uses bubble sort algorithm to sort the cities from order of highest average July temp to the lowest (descending order)
    sort_cities();

    // Prints the header for the program
    printf("\nAverage July Temperatures by City\n\n");

    // Prints all of the elements, including the city name and average highest July temp, from highest to lowest temps
    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// Uses bubble sort algorithm to sort the cities from order of highest average July temp to the lowest (descending order)
void sort_cities(void)
{
    // Set counter initially to a non-zero number so we can start the while loop
    int counter = 1;

    // Declare a buffer variable (stores city and temp) that we can use temporarily to help with swapping (so we don't lose any values)
    avg_temp buffer;

    // Continue going through the loop to do a check through to see if swaps need to be made, as long as the last check did not contain 0 swaps
    // If the last check contained 0 swaps, then the temps should be sorted and the program is finished
    while (counter != 0)
    {
        // Reset counter to 0 so we can count how many swaps are made in each check through
        counter = 0;

        // Check from the first element to the 2nd last one (due to comparing i and i+1)
        for (int i = 0; i < NUM_CITIES - 1; i++)
        {
            // Compare the temps for i and i+1, if not in correct descending order then make a swap
            if (temps[i].temp < temps[i + 1].temp)
            {
                // Make a swap with adjacent elements by using the buffer variable to store values
                buffer = temps[i];
                temps[i] = temps[i + 1];
                temps[i + 1] = buffer;

                // Counter should be incremented if swaps were made, so the loop can be repeated until no swaps need to be made
                counter++;
            }
        }
    }
}
