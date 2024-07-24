# The 'scoresadvanced' program allows the user to input the number of scores and each score to calculate the average
# This version is more advanced and will reprompt the user if they input non-integer values or negative values

# Define scores as an empty list to fill
scores = []

while True:
    # Get the number of scores from the user
    try:
        n = int(input("Number of scores: "))
        if n < 1:
            print("Number must be positive")
            continue
    except ValueError:
        print("Number must be an integer")
        continue

    # Get the scores from the user
    for i in range(n):
        while True:
            try:
                score = int(input("Score: "))
                if score < 0:
                    print("Number must be greater than or equal to zero")
                    continue
                scores.append(score)
                break
            except ValueError:
                print("Score must be an integer")
                continue

    # Calculate and print out the average of the scores
    average = sum(scores) / len(scores)
    print(f"Average is {average:.2f}%")
    break

