# The 'tournament' program simulate a FIFA sports tournament and gives the probability of teams that will win during a tournamnet
# The user can input a csv file (containing teams and their FIFA ratings) as a command-line argument: python tournament.py [FILENAME]
# The program then populates the csv file into a list of dictionaries of the teams and their ratings
# Then it simulates an N number of tournaments, where each tournament consists of knockout round between pairs of teams to determine the winner
# Number of wins for each team is then added to a dictionary with teams and win counts, used to determine the probability of each team winning
# The teams and probabilities of winning are then printed in descending order

import csv
import sys
import random

# Number of FIFA simluation tournaments to run
N = 1000


def main():

    # Ensure correct usage (only 1 command-line argument inputed by the user)
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py [FILENAME]")

    # Read teams into memory from file
    # Open the csv file from the command-line argument
    # Each csv row is read as a dictionary and added to the teams list (contains all dictionaries each with a team (key) and rating (key))
    # The ratings are also converted to integers (from strings)
    teams = []
    with open(sys.argv[1], "r") as file:
        filereader = csv.DictReader(file)
        for fifateam in filereader:
            fifateam["rating"] = int(fifateam["rating"])
            teams.append(fifateam)

    # Simulate N tournaments and keep track of win counts
    # Win counts are added to the counts dictionary (contains team names (key) and number of wins (value))
    counts = {}
    for i in range(N):
        winner = simulate_tournament(teams)
        if winner in counts:
            counts[winner] += 1
        else:
            counts[winner] = 1

    # Print each team's chances of winning (probability) in descending order according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


# Simulates a game. Return True if team1 wins, False otherwise
# Probability of winning formula is used, and some randomness is used to determine which team will win
def simulate_game(team1, team2):
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


# Simulate a round of knockouts (1 vs 1 team matches) between the remaining teams
# Return a list of winning teams
def simulate_round(teams):
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])
    return winners

# Simulate a tournament with multiple knockout rounds (1 vs 1 team matches) until only 1 team remains
# Return name of winning team
def simulate_tournament(teams):
    while len(teams) > 1:
        teams = simulate_round(teams)
    if len(teams) == 1:
        return teams[0]["team"]


# Call the main function to starting running the program
if __name__ == "__main__":
    main()
