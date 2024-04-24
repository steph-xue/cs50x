// The 'stringinput1' program shows the first way to get a string input from the user, programming in c language
        // Using the scanf("%s", [variable])
        // This can only be used for single words as it doesn't take in words after white spaces

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Allocate memory for the string using an array (or can use malloc)
    char name[15];

    // Can print the prompt and then use the format scanf("%s", [variable])
    // This can only be used for single words as it doesn't take in words after white spaces
    printf("What is your name?: ");
    scanf("%s", name);
    printf("Name is %s\n", name);
}
