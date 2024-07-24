// The "mario" program prompts the user to specify the size of bricks and prints the bricks to the screen in a square format with 'n' size

#include <cs50.h>
#include <stdio.h>

int get_size(void);
void printbricks(int n);

int main(void)
{
    // Get 'n' size of bricks from user
    int n = get_size();

    // Print bricks in a square format according to 'n' size
    printbricks(n);
}


// Get 'n' size of bricks from user
int get_size(void)
{
    int n;
    do
    {
        n = get_int("What size of bricks?: ");
    }
    while (n < 1);
    return n;
}


// Print bricks in a square format according to 'n' size
void printbricks(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
