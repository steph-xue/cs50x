// The 'snackbar' program prints out a list of menu items and their prices for Beach Burger Shack
// When prompted, the user can input which menu item(s) they want to purchase (case insensitive) one at a time and press enter when they are done
// The program then prints out the corresponding total of the costs of the items the user wants to purchase
    // Practice using structs
    // Practice writing a linear search function

/**
 * Beach Burger Shack has the following 10 items on their menu:
    * Burger: $9.5
    * Vegan Burger: $11
    * Hot Dog: $5
    * Cheese Dog: $7
    * Fries: $5
    * Cheese Fries: $6
    * Cold Pressed Juice: $7
    * Cold Brew: $3
    * Water: $2
    * Soda: $2
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Number of menu items
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 10

// Menu itmes have item name and price
typedef struct
{
    string item;
    float price;
}
menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Function prototypes
void add_items(void);
bool validitem(string item);
float get_cost(string item);

int main(void)
{
    // Add items to the menu
    add_items();

    // Prints out the welcome message and instructions for ordering
    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    // Prints out a list of the menu items and prices
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    }
    printf("\n");

    // Set the total cost initial to 0 so we can sum the item costs up
    float total = 0;

    // Loop starts to get the user to input the menu items they want to buy
    while (true)
    {
        // Gets user to input the menu items they want to buy
        string item = get_string("Enter a food item: ");

        // If the item is not on the menu, it prints that it is an invalid item
        if (!validitem(item))
        {
            printf("Invalid item\n");
        }

        // If the user presses enter to end their order, it breaks the loop
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        // Determines the cost of the item inputed by the user and adds it to their total cost
        total += get_cost(item);
    }

    // Prints out the total cost the user owes for the menu items requested
    printf("Your total cost is: $%.2f\n", total);
}

// Add items to the menu
void add_items(void)
{
    menu[0].item = "Burger";
    menu[0].price = 9.50;

    menu[1].item = "Vegan Burger";
    menu[1].price = 11.00;

    menu[2].item = "Hot Dog";
    menu[2].price = 5.00;

    menu[3].item = "Cheese Dog";
    menu[3].price = 7.00;

    menu[4].item = "Fries";
    menu[4].price = 5.00;

    menu[5].item = "Cheese Fries";
    menu[5].price = 6.00;

    menu[6].item = "Cold Pressed Juice";
    menu[6].price = 7.00;

    menu[7].item = "Cold Brew";
    menu[7].price = 3.00;

    menu[8].item = "Water";
    menu[8].price = 2.00;

    menu[9].item = "Soda";
    menu[9].price = 2.00;

    return;
}

// Determines if the menu item inputed by the user is valid (on the menu)
bool validitem(string item)
{
    // Goes through each item on the menu
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        // Sees if the menu item inputed by the user matches any of the items on the menu (both converted to lowercase as it needs to be case insensitive)
        // If a match is found, returns true
        if (strcasecmp(menu[i].item, item) == 0)
        {
            return true;
        }
    }
    // If cannot be found on the menu, returns false
    return false;
}

// Search through the menu array to find an item's cost
float get_cost(string item)
{
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (strcasecmp(menu[i].item, item) == 0)
        {
            return menu[i].price;
        }
    }
    return 0;
}
