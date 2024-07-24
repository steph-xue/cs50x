// The "credit" program allows the user to input a credit card number and tells if it is a valid VISA, MASTERCARD or AMEX or an INVALID card
// Credit card validity is based on if it follows Luhn's algorithm, as well as the length and beginning digits based on the following below
// This is the 2nd solution involving functions

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

long get_number(void);
int countcard(long number);
bool luhnsvalidity(long number);
bool visavalidity(long number, int count);
bool mastercardvalidity(long number, int count);
bool amexvalidity(long number, int count);


int main(void)
{
    // Get the user to input their credit card number
    long number = get_number();

    // Determines the length of the credit card (dividing by 10 until there are no digits left)
    int count = countcard(number);

    // Determines and prints if the credit card is INVALID through Luhn's algorithm
    if (luhnsvalidity(number) == false)
    {
        printf("INVALID\n");
        return 0;
    }

    // Determines and prints if the credit card is a valid VISA (13 or 16 digits long AND starts with 4)
    if (visavalidity(number, count) == true)
    {
        printf("VISA\n");
        return 0;
    }

    // Determines and prints if the credit card is a valid MasterCard (16 digits long AND starts with 51, 52, 53, 54, or 55)
    if (mastercardvalidity(number, count) == true)
    {
        printf("MASTERCARD\n");
        return 0;
    }

    // Determines and prints if the credit card is a valid AMEX (15 digits long AND starts with 34 or 37)
    if (amexvalidity(number, count) == true)
    {
        printf("AMEX\n");
        return 0;
    }

    // Determines and prints if the credit card is INVALID otherwise
    else
    {
        printf("INVALID\n");
        return 0;
    }
}


// Get the user to input their credit card number
long get_number(void)
{
    long number;
    do
    {
        number = get_long("What is the credit card number? (no spaces/hypens): ");
    }
    while (number < 1);
    return number;
}


// Determines and prints if the credit card is invalid through Luhn's algorithm
bool luhnsvalidity(long number)
{
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

    if ((sumtotal % 10) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// Determines the length of the credit card (dividing by 10 until there are no digits left)
int countcard(long number)
{
    int count = 0;
    while (number > 0)
    {
        number /= 10;
        count++;
    }
    return count;
}

// Determines and prints if the credit card is a valid VISA (13 or 16 digits long AND starts with 4)
bool visavalidity(long number, int count)
{
    while (number >= 10)
    {
        number /= 10;
    }
    if (number == 4 && (count == 13 || count == 16))
    {
        return true;
    }
    else
    {
        return false;
    }
}


// Determines and prints if the credit card is a valid MasterCard (16 digits long AND starts with 51, 52, 53, 54, or 55)
bool mastercardvalidity(long number, int count)
{
    while (number >= 100)
    {
        number /= 10;
    }
    if ((number == 51 || number == 52 || number == 53 || number == 54 || number == 55) && count == 16)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// Determines and prints if the credit card is a valid AMEX (15 digits long AND starts with 34 or 37)
bool amexvalidity(long number, int count)
{
    while (number>= 100)
    {
        number /= 10;
    }
    if ((number == 34 || number == 37) && count == 15)
    {
        return true;
    }
    else
    {
        return false;
    }
}
