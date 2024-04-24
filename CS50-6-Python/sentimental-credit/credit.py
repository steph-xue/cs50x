# The "credit" program allows the user to input a credit card number and tells if it is a valid VISA, MASTERCARD or AMEX or an INVALID card
# Credit card validity is based on if it follows Luhn's algorithm, as well as the length and beginning digits based on the following below
# This is the 1st solution involving functions

# MASTERCARD: 16 digit length, starts with 51, 52, 53, 54, or 55
# VISA: 13 or 16 digit length, starts with 4
# AMEX: 15 digit length, starts with 34 or 37

# Luhn's Algorithm:
# 1. Starting with the 2nd last card number, multiply every 2nd digit by 2
# 2. Add the sum of each individual digit obtained in all the products above
# 3. Add the sum of the other digits in the card, starting with the last number
# 4. If the total sum of everything ends with a 0, it is valid!

import sys

def main():

    # Get the user to input their credit card number
    number = get_number()

    # Determines and prints if the credit card is invalid based on the length
    if len(str(number)) > 16 or len(str(number)) < 13:
        print('INVALID')
        sys.exit(1)

    # Determines and prints if the credit card is INVALID through Luhn's algorithm
    if not luhnsvalidity(number):
        print('INVALID')
        sys.exit(1)

    # Determines and prints if the credit card is a valid MasterCard (16 digits long AND starts with 51, 52, 53, 54, or 55)
    if mastercardvalidity(number):
        print('MASTERCARD')
        sys.exit(0)

    # Determines and prints if the credit card is a valid VISA (13 or 16 digits long AND starts with 4)
    if visavalidity(number):
        print('VISA')
        sys.exit(0)

    # Determines and prints if the credit card is a valid AMEX (15 digits long AND starts with 34 or 37)
    if amexvalidity(number):
        print('AMEX')
        sys.exit(0)

    # Determines and prints if the credit card is INVALID otherwise
    else:
        print('INVALID')
        sys.exit(1)

# Get the user to input their credit card number
# Must be numbers only and must be positive
def get_number():
    while True:
        try:
            number = int(input('Credit card number: '))
            if number > 1:
                break
        except ValueError:
            print('Must be a positive number')
            continue
    return number


#Determines and prints if the credit card is invalid through Luhn's algorithm
def luhnsvalidity(number):

    # Starting from the 2nd last card digit, determines the product of every 2nd digit multiplied by 2 (8 products assumming max card length is 16 digits)
    card1 = int((number % 10**2)/10) * 2
    card2 = int((number % 10**4)/10**3) * 2
    card3 = int((number % 10**6)/10**5) * 2
    card4 = int((number % 10**8)/10**7) * 2
    card5 = int((number % 10**10)/10**9) * 2
    card6 = int((number % 10**12)/10**11) * 2
    card7 = int((number % 10**14)/10**13) * 2
    card8 = int((number % 10**16)/10**15) * 2

    # Determines the sum of each individual digit within all products obtained above (these are 1-2 digit products)
    card1 = int((card1 % 10**2) / 10) + (card1 % 10)
    card2 = int((card2 % 10**2) / 10) + (card2 % 10)
    card3 = int((card3 % 10**2) / 10) + (card3 % 10)
    card4 = int((card4 % 10**2) / 10) + (card4 % 10)
    card5 = int((card5 % 10**2) / 10) + (card5 % 10)
    card6 = int((card6 % 10**2) / 10) + (card6 % 10)
    card7 = int((card7 % 10**2) / 10) + (card7 % 10)
    card8 = int((card8 % 10**2) / 10) + (card8 % 10)

    # Determines the complete sum of all the individual digits of all the products above (every 2nd digit from the 2nd last digit)
    sum1 = card1 + card2 + card3 + card4 + card5 + card6 + card7 + card8

    # Starting from the last card digit, determines the value of every 2nd digit (8 digits assumming max card length is 16 digits)
    cardx1 = int(number % 10)
    cardx2 = int((number % 10**3)/10**2)
    cardx3 = int((number % 10**5)/10**4)
    cardx4 = int((number % 10**7)/10**6)
    cardx5 = int((number % 10**9)/10**8)
    cardx6 = int((number % 10**11)/10**10)
    cardx7 = int((number % 10**13)/10**12)
    cardx8 = int((number % 10**15)/10**14)

    # Determines the complete sum of all the individual digits above (every 2nd digit from the last digit)
    sum2 = cardx1 + cardx2 + cardx3 + cardx4 + cardx5 + cardx6 + cardx7 + cardx8

    # Determines the total sum of all the digits
    sumtotal = sum1 + sum2

    if (sumtotal % 10) == 0:
        return True
    else:
        return False


# Determines and prints if the credit card is a valid MasterCard (16 digits long AND starts with 51, 52, 53, 54, or 55)
def mastercardvalidity(number):

    mc = number
    while mc >= 100:
        mc = int(mc / 10)

    if len(str(number)) == 16 and (mc == 51 or mc == 52 or mc == 53 or mc == 54 or mc == 55):
        return True
    else:
        return False


# Determines and prints if the credit card is a valid VISA (13 or 16 digits long AND starts with 4)
def visavalidity(number):

    visa = number
    while visa >= 10:
       visa = int(visa / 10)

    if (len(str(number)) == 13 or len(str(number)) == 16) and (visa == 4):
        return True
    else:
        return False


# Determines and prints if the credit card is a valid AMEX (15 digits long AND starts with 34 or 37)
def amexvalidity(number):

    amex = number
    while amex >= 100:
        amex = int(amex / 10)

    if len(str(number)) == 15 and (amex == 34 or amex == 37):
        return True
    else:
        return False


if __name__ == "__main__":
    main()
