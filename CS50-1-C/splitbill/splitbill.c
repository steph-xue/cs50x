// The "half" program prompts the user to input the cost of the bill, sales tax percent, and tip percent
// The program calculates how much each person will have to pay after sales tax and tip

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get the user to input the number of people, total bill before tax and tip, the sales tax percent, and the tip percent
    int people = get_int("Number of people: ");
    float bill = get_float("Bill before tax and tip: $ ");
    float tax = get_float("Sale tax percent (%%): ");
    float tip = get_float("Tip percent (%%): ");

    // Calculates the post tax cost, post tip cost, and the total each person will have to pay after sales tax and tip
    float posttax = bill + (bill * (tax / 100));
    float posttip = posttax + (posttax * (tip / 100));
    float splitbill = posttip / people;

    // Prints the amount of money each person will have to pay after sales tax and tip
    printf("You will owe $%0.2f each!\n", splitbill);

}
