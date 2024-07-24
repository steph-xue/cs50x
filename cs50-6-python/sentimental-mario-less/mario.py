# The "mario" program prompts the user to specify the size of bricks (between 1-8) and prints an end-of-game staircase according to n size

def main():
    # Get 'n' size of bricks from user
    n = get_size()

    # Print bricks in a staircase format according to 'n' size
    print_bricks(n)


# Get 'n' size of bricks from user
# Reprompts the user if the number is not between 1 and 8, and if it is not an integer
def get_size():
    while True:
        try:
            n = int(input("What size of bricks? (between 1 and 8): "))
            if n >= 1 and n <=8:
                break
        except ValueError:
            print("Input should be an integer between 1 and 8")
            continue
    return n


# Print bricks in a staircase format according to 'n' size
def print_bricks(n):

    for i in range(n):

        for space in range(0, n - (i + 1)):
            print(" ", end="")

        for brick in range(0, i + 1):
            print("#", end="")

        print("")


# Call the main function to starting running the program
if __name__ == "__main__":
    main()
