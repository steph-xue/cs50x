# The "comparisonxy" program allows the user to input 2 integers as x and y, and tells the user if x is greater than, less than, or equal to y

# input() function gets strings but int() type casts it into an int
# If the user inputs a non-integer, it will re-prompt the user to input integers (using the try and except conditionals)

while True:
    try:
        x = int(input("What is x? "))
        y = int(input("What is y? "))

        if x < y:
            print("x is less than y")
            break
        elif x > y:
            print("x is greater than y")
            break
        else:
            print("x is equal to y")
            break
    except ValueError:
        print("x and y must be integers")


