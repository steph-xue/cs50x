// The 'pointer' program allows us to practice and understand the use of pointers in C language
// Determine what would be printed out as variables a, b, and c, and then run the program to check you answer

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int a = 28;
    int b = 50;
    int *c = &a;

    *c = 14;
    c = &b;
    *c = 25;

    // Print results of the answers
    printf("a has the value %i, located at %p\n", a, &a);
    printf("b has the value %i, located at %p\n", b, &b);
    printf("c has the value %p, located at %p\n", c, &c);
}
