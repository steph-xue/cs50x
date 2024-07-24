// The "comparison" program allows the user to input 2 integers as x and y, and tells the user if x is greater than, less than, or equal to y

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Gets the user to input integers for x and y
    int x = get_int("What is x? (integer only): ");
    int y = get_int("What is y? (integer only): ");

    //Conditionals to determine if x is greater than, less than, or equal to y and then prints it on the screen
    if (x > y)
    {
        printf("x is greater than y\n");
    }
    else if (x < y)
    {
        printf("x is less than y\n");
    }
    else if (x == y)
    {
        printf("x is equal to y\n");
    }
}
