# The "cash" program gets users to input change (cents) and finds the number of coins, quarters, dimes, nickles, and pennies to yield the least amount

def main():
    # Ask how many cents the customer is owed
    cents = get_cents()

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1

    # Calculate the total number of coins by summing the number of each coin type
    totalcoins = quarters + dimes + nickels + pennies

    # Print total number of coins, quarters, dimes, nickles, and pennies to give the customer
    print(f'Total coins:{totalcoins}')
    print(f'Quarters: {quarters}')
    print(f'Dimes: {dimes}')
    print(f'Nickels: {nickels}')
    print(f'Pennies: {pennies}')


# Ask how many cents the customer is owed
def get_cents():
    while True:
        try:
            cents = float(input('Change owed ($): '))
            if cents > 0:
                break
        except ValueError:
            print('Change needs to be a positive real number')
            continue
    return round(cents * 100)


# Calculate the number of quarters to give the customer
def calculate_quarters(cents):
    quarters = 0
    while cents >= 25:
        cents = cents - 25
        quarters += 1
    return quarters


# Calculate the number of dimes to give the customer
def calculate_dimes(cents):
    dimes = 0
    while cents >= 10:
        cents = cents - 10
        dimes += 1
    return dimes

# Calculate the number of nickels to give the customer
def calculate_nickels(cents):
    nickels = 0
    while cents >= 5:
        cents = cents - 5
        nickels += 1
    return nickels


# Calculate the number of pennies to give the customer
def calculate_pennies(cents):
    pennies = 0
    while cents >= 1:
        cents = cents - 1
        pennies += 1
    return pennies


if __name__ == "__main__":
    main()
