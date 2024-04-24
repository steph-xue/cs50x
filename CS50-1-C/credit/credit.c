// The "credit" program allows the user to input a credit card number and tells if it is a valid VISA, MASTERCARD or AMEX or an INVALID card
// Credit card validity is based on if it follows Luhn's algorithm, as well as the length and beginning digits based on the following below
// This is the 1st solution that doesn't involve functions

// MASTERCARD: 16 digit length, starts with 51, 52, 53, 54, or 55
// VISA: 13 or 16 digit length, starts with 4
// AMEX: 15 digit length, starts with 34 or 37

// Luhn's Algorithm:
// 1. Starting with the 2nd last card number, multiply every 2nd digit by 2
// 2. Add the sum of each individual digit obtained in all the products above
// 3. Add the sum of the other digits in the card, starting with the last number
// 4. If the total sum of everything ends with a 0, it is valid!


#include <cs50.h>
#include <stdio.h>


int main(void)
{
    // Get the user to input their credit card number
    long number;
    do
    {
        number = get_long("What is the credit card number? (no spaces/hypens): ");
    }
    while (number < 1);



    // Determines and prints if the credit card is invalid through Luhn's algorithm

    // Starting from the 2nd last card digit, determines the product of every 2nd digit multiplied by 2 (8 products assumming max card length is 16 digits)
    long card1, card2, card3, card4, card5, card6, card7, card8;
    card1 = (((number % 100)/10) * 2);
    card2 = (((number % 10000)/1000) * 2);
    card3 = (((number % 1000000)/100000) * 2);
    card4 = (((number % 100000000)/10000000) * 2);
    card5 = (((number % 10000000000)/1000000000) * 2);
    card6 = (((number % 1000000000000)/100000000000) * 2);
    card7 = (((number % 100000000000000)/10000000000000) * 2);
    card8 = (((number % 10000000000000000)/1000000000000000) * 2);

    // Determines the sum of each individual digit within all products obtained above (these are 1-2 digit products)
    card1 = ((card1 % 100)/10) + (card1 % 10);
    card2 = ((card2 % 100)/10) + (card2 % 10);
    card3 = ((card3 % 100)/10) + (card3 % 10);
    card4 = ((card4 % 100)/10) + (card4 % 10);
    card5 = ((card5 % 100)/10) + (card5 % 10);
    card6 = ((card6 % 100)/10) + (card6 % 10);
    card7 = ((card7 % 100)/10) + (card7 % 10);
    card8 = ((card8 % 100)/10) + (card8 % 10);

    // Determines the complete sum of all the individual digits of all the products above (every 2nd digit from the 2nd last digit)
    long sum1 = card1 + card2 + card3 + card4 + card5 + card6 + card7 + card8;

    // Starting from the last card digit, determines the value of every 2nd digit (8 digits assumming max card length is 16 digits)
    long cardx1, cardx2, cardx3, cardx4, cardx5, cardx6, cardx7, cardx8;
    cardx1 = (number % 10);
    cardx2 = ((number % 1000)/100);
    cardx3 = ((number % 100000)/10000);
    cardx4 = ((number % 10000000)/1000000);
    cardx5 = ((number % 1000000000)/100000000);
    cardx6 = ((number % 100000000000)/10000000000);
    cardx7 = ((number % 10000000000000)/1000000000000);
    cardx8 = ((number % 1000000000000000)/100000000000000);

    // Determines the complete sum of all the individual digits above (every 2nd digit from the last digit)
    long sum2 = cardx1 + cardx2 + cardx3 + cardx4 + cardx5 + cardx6 + cardx7 + cardx8;

    // Determines the total sum of all the digits
    long sumtotal = sum1 + sum2;

    if ((sumtotal % 10) != 0)
    {
        printf("INVALID\n");
        return 0;
    }



    // Determines and prints if the credit card is a valid VISA, MasterCard, or AMEX (based on length and first 1-2 digits) or invalid otherwise

    // Determines the length of the credit card (dividing by 10 until there are no digits left)
    int count = 0;
    long numbercount = number;
    while (numbercount > 0)
    {
        numbercount /= 10;
        count++;
    }

    // Determines and prints if the credit card is a valid VISA (13 or 16 digits long AND starts with 4)
    long visa = number;
    while (visa >= 10)
    {
        visa /= 10;
    }
    if (visa == 4 && (count == 13 || count == 16))
    {
        printf("VISA\n");
        return 0;
    }

    // Determines and prints if the credit card is a valid MasterCard (16 digits long AND starts with 51, 52, 53, 54, or 55)
    long mastercard = number;
    while (mastercard >= 100)
    {
        mastercard /= 10;
    }
    if ((mastercard == 51 || mastercard == 52 || mastercard == 53 || mastercard == 54 || mastercard == 55) && count == 16)
    {
        printf("MASTERCARD\n");
        return 0;
    }

    // Determines and prints if the credit card is a valid AMEX (15 digits long AND starts with 34 or 37)
    long amex = number;
    while (amex >= 100)
    {
        amex /= 10;
    }
    if ((amex == 34 || amex == 37) && count == 15)
    {
        printf("AMEX\n");
        return 0;
    }

    // If not a valid VISA, MasterCard, or AMEX credit card, prints invalid card
    else
    {
        printf("INVALID\n");
        return 0;
    }
}
