// The 'tempsselectionsort' program takes an array that contains a list of cities and their average highest July temps (element contains name of city and temp)
// The array is unsorted, and the program uses the selection sorting algorithm to sort the elements from highest to lowest July temperatures
    // Practice working with structs
    // Practice applying selection sorting algorithm

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

    // Uses selection sort algorithm to sort the cities from order of highest average July temp to the lowest (descending order)
    sort_cities();

    // Prints the header for the program
    printf("\nAverage July Temperatures by City\n\n");

    // Prints all of the elements, including the city name and average highest July temp, from highest to lowest temps
    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// Uses selection sort algorithm to sort the cities from order of highest average July temp to the lowest (descending order)
void sort_cities(void)
{
    // Defines the highest index so we can keep track of the element with the highest temp
    int highest_index;

    // Declare a buffer variable (stores city and temp) that we can use temporarily to help with swapping (so we don't lose any values)
    avg_temp buffer;

    // For each 'ith' element, goes through the rest of the unsorted array to swap the highest temp element with the 'ith' element
    for (int i = 0; i < NUM_CITIES; i++)
    {
        // Declares the higest index initially as just 'i' so we can compare the rest of the unsorted array and swap indexes as needed
        highest_index = i;

        // Goes through the rest of the unsorted array (starting from i + 1)
        for (int j = i + 1; j < NUM_CITIES; j++)
        {
            // If the temp of index 'j' is higher than the current highest temp index, then replace the highest index with the current 'j' index
            if (temps[highest_index].temp < temps[j].temp)
            {
                highest_index = j;
            }
        }

        // After finding the index with the highest temp, make a swap with the 'ith' element by using the buffer variable to store values
        buffer = temps[i];
        temps[i] = temps[highest_index];
        temps[highest_index] = buffer;
    }
}
