// The 'hours' program allows the user to input the number of weeks taking CS50 and the number of hours spent per week
// The user can specify the program to calculate the total number of hours with 'T' or 't' or the average number of hours with 'A' or 'a'

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    // Get user to input the number of weeks taking CS50
    int weeks = get_int("Number of weeks taking CS50: ");

    // Create an array to store the number of hours spent on each week of CS50
    int hours[weeks];

    // Get the user to input the number of hours spent on each week of CS50, and input these into the array 'hours'
    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    // Get the user to input 'T' for total hours or 'A' for average hours (either uppercase or lowercase)
    // Reprompts the user if they do not enter 'T', 't', 'A', or 'a'
    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    // Calculates and prints out the total/average number of hours depending on what the user specified for the type of output
    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// Calculates the total/average number of hours depending on what the user specified for the type of output
float calc_hours(int hours[], int weeks, char output)
{
    // Calculates the total number of hours using the array of hours stored in hours[]
    float totalhours = 0;
    for (int i = 0; i < weeks; i++)
    {
        totalhours += hours[i];
    }

    // Returns the total number of hours if the user specified for 'T'
    if (output == 'T')
    {
        return totalhours;
    }

    // Returns the total number of hours if the user specified for 'A'
    else
    {
        return totalhours / weeks;
    }
}
