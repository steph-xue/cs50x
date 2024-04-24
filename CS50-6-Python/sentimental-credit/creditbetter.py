# The "credit" program allows the user to input a credit card number and tells if it is a valid VISA, MASTERCARD or AMEX or an INVALID card
# Credit card validity is based on if it follows Luhn's algorithm, as well as the length and beginning digits based on the following below
# This is the 2nd solution that has a better optimized Luhn's algorithm

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


# Determines and prints if the credit card is invalid through Luhn's algorithm
def luhnsvalidity(number):

    # Function that takes a number and returns a list of digits in the number
    # Converts number to a string and iterates through each character, turning them into integers in a new list
    def makedigitslist(n):
        return [int(d) for d in str(n)]

    # Obtains a list of digits in the card number
    digitslist = makedigitslist(number)

    # Gets a list of every 2nd digit starting from the last digit (oddnumberslist)
    # Gets a list of every 2nd digit starting from the 2nd last digit (evennumberslist)
    oddnumberslist = digitslist[-1::-2]
    evennumberslist = digitslist[-2::-2]

    # Adds the sum of all digits in the oddnumberslist to the totalsum
    totalsum = 0
    totalsum += sum(oddnumberslist)

    # Takes each digit in the evennumberslist, multiplies by 2, and adds the sum of all digits of the products to the totalsum
    for d in evennumberslist:
        totalsum += sum(makedigitslist(d*2))

    if totalsum % 10 == 0:
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
