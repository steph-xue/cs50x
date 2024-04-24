# The 'text' program is an exercise on for loops to see if you can determine what will print out during each round

text = "In the great green room"
words = text.split()

# Round 1
print("Round 1")
for word in words:
    print(word)
print()

# In
# the
# great
# green
# room


# Round 2
print("Round 2")
for word in words:
    for c in word:
        print(c)
print()

# I
# n
# t
# h
# e
# etc, etc...


# Round 3
print("Round 3")
for word in words:
    if "g" in word:
        print(word)
print()

# great
# green


# Round 4
print("Round 4")
for word in words[2:]:
    print(word)
print()

# great
# green
# room


# Round 5
print("Round 5")
for word in words:
    print("Goodnight Moon")
print()

# Goodnight Moon
# Goodnight Moon
# Goodnight Moon
# Goodnight Moon
# Goodnight Moon
