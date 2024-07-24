// The 'stringinput2' program shows the second way to get a string input from the user, programming in c language
        // Using the scanf("%[^\n]%*c", [variable])
        // This takes in words including white spaces, stopping when a new line is generated as in the '^\n'

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Allocate memory for the string using an array (or can use malloc)
    char name[15];

    // Can print the prompt and then use the format scanf("%s", [variable])
    // This takes in words including white spaces, stopping when a new line is generated as in the '^\n'
    printf("What is your name?: ");
    scanf("%[^\n]%*c", name);
    printf("Name is %s\n", name);
}
