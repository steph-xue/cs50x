# The 'hello' program gets user input (a name), and will print out hello and the user's name
# It shows different ways to print strings with variables
# Note: get_string is specific to the cs50 library

# Add on variable using the + (adds without space)
answer = input("What is your name? ")
print("hello, " + answer)

# Add on variable using a comma (adds with space)
answer = input("What is your name? ")
print("hello,", answer)

# Use f format code within the brackets to substitute variables in the curly braces
answer = input("What is your name? ")
print(f"hello, {answer}")
