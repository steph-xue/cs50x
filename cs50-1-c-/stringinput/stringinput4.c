// The 'stringinput4' program shows the fourth way to get a string input from the user, programming in c language
        // Using the fgets([variable], size, stdin)
        /// This takes in words including white spaces (stops only when a new line is generated), and limits the size specified

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Allocate memory for the string using an array (or can use malloc)
    char name[15];

    // Can print the prompt and then use the format fgets([variable], size, stdin)
    // This takes in words including white spaces (stops only when a new line is generated), and limits the size specified
    printf("What is your name?: ");
    fgets(name, 15, stdin);
    printf("Name is %s\n", name);


}
