# The 'calculator' program simply gets 2 numbers from the user to divide

# Get input from the user ()
# input() function gets strings but int() type casts it into an int
# If the user inputs a non-integer, it will re-prompt the user to input integers (using the try and except conditionals)

while True:
    try:
        x = int(input("x: "))
        y = int(input("y: "))

        z = x / y

        # Prints the answer and the answer to 50 decimal places (float)
        print(f"{z}")
        print(f"{z:.50f}")
        break
    except ValueError:
        print("x and y must be integers")
