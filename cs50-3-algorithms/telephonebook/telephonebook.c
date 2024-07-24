// The 'telephonebook' program allows the user to input a name to find in the telephone book, and if found prints out the number
// If name not found, prints out the name cannot be found
// Practicing defining a new data type (with different data types stored) with linear search to search through an array

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Define a new data type that contains a name and number as both 'strings'
typedef struct
{
    string name;
    string number;
}
telephonebook;

// Define the size of the telephone book
const int size = 2;

int main(void)
{
    // Creates an array for the telephone book with the data type containing both names and numbers as defined as 'telephonebook'
    telephonebook people[size];

    // Assigning names and numbers to each element of the array (names and numbers are linked together as a data type)
    people[0].name = "Stephanie";
    people[0].number = "(778)680-1033";

    people[1].name = "Kasey";
    people[1].number = "(519)801-7135";

    // Gets the user to input a name to look up
    string s = get_string("What name do you want to look up?: ");

    // Uses linear search to check for the name in the array, and then if found prints out the number
    // If not found, prints out name cannot be found
    for (int i = 0; i < size; i++)
    {
        if (strcmp(people[i].name, s) == 0)
        {
            printf("Number is: %s\n", people[i].number);
            return 0;
        }
    }
    printf("Name cannot be found\n");
    return 1;
}
