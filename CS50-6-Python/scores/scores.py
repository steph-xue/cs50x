# The 'scoresadvanced' program allows the user to input the number of scores and each score to calculate the average
# This easier version assumes the user will not type in non-integer values or negative values

# Define scores as an empty list to fill
scores = []

# Get the number of scores from the user
n = int(input("Number of scores: "))


# Get the scores from the user
for i in range(n):
    score = int(input("Score: "))
    scores.append(score)

# Calculate and print out the average of the scores
average = sum(scores) / len(scores)
print(f"Average is {average:.2f}%")

