// The "mario" program prompts the user to specify the size of bricks (between 1-8) and prints front and back stairs to jump over according to n size

#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_bricks(int n);

int main(void)
{
    // Get 'n' size of bricks from user
    int n = get_size();

    // Print bricks in a front and back stairs format according to 'n' size
    print_bricks(n);
}


// Get 'n' size of bricks from user
int get_size(void)
{
    int n;
    do
    {
        n = get_int("What size of bricks? (1-8): ");
    }
    while (n < 1 || n > 8);
    return n;
}


// Print bricks in a front and back stairs format according to 'n' size
void print_bricks(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int space = 0; space < n - (i + 1); space++)
        {
            printf(" ");
        }

        for (int frontbricks = 0; frontbricks < i + 1; frontbricks++)
        {
            printf("#");
        }

        printf("  ");

        for (int backbricks = 0; backbricks < i + 1; backbricks++)
        {
            printf("#");
        }
        printf("\n");
    }
}
