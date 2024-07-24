# The "dna" program allows the user to input 2 command-line arguments: the DNA database .csv file and the unidentified DNA .txt file
    # dna.py [.csv] [.txt]
    # The DNA database .csv file has columns for name and each STR sequence, and rows for each individual (name, STR counts)
    # The DNA .txt file contains a DNA sequence
# The program uses the DNA database to identify the name of the individual who's DNA matches the unidentified DNA, or determines if there is no match
    # It uses the STR sequences in the DNA database file to calculate the longest consecutive counts of each STR in the unidentified DNA
    # It then matches the STR counts to individuals in the DNA database file based on each individual's STR counts (all must match)
    # The program then prints out who's DNA the .txt file matches (if there is a match) or prints out if there is no match


import csv
import sys


def main():

    """
    Check for command-line usage
    """

    # Must have 2 command-line arguments: the DNA database .csv file and the unidentified DNA .txt file)
    if len(sys.argv) != 3:
        print("Usage: dna.py [.csv] [.txt]")
        sys.exit(1)


    # Check to make sure first command-line argument is a .csv file (DNA database)
    if not sys.argv[1].endswith(".csv"):
        print("First command-line argument must be .csv file (dna database)")
        sys.exit(1)


    # Check to make sure second command-line argument is a .txt file (unidentified DNA)
    if not sys.argv[2].endswith(".txt"):
        print("Second command-line argument must be .txt file (unidentified dna)")
        sys.exit(1)


    """
    Read database DNA file into a variable
    """

    # Create list of dictionaries, each dictionary representing an individual (including name and counts for STR sequences) from the database DNA file
    peoplelist = []

    # Create list of STR sequences from the database DNA file
    strlist = []

    # Open and read the database DNA .csv file to save to the lists
    with open(sys.argv[1]) as file:
        filereader = csv.DictReader(file)
        strlist = filereader.fieldnames[1:]
        for row in filereader:
            peoplelist.append(row)


    """
    Read unidentified DNA sequence file into a variable
    """

    # Open and read the unidentified DNA sequence .txt file to save to a variable
    with open(sys.argv[2]) as file:
        dna = file.read()


    """
    Find longest match of each STR in DNA sequence
    """

    # Create a dictionary to store counts for STR sequences for the unidentified DNA sequence
    dnastrcounts = {}

    # Determines the longest consecutive count of each STR for the unidentified DNA sequence to store in the dnastrcounts dictionary
    for str in strlist:
        strlength = longest_match(dna, str)
        dnastrcounts[str] = strlength


    """
    Check database for matching profiles
    """

    # Determines the total number of STR sequences (all must match to identify an individual)
    strsequencecount = len(strlist)

    # Iterates through each individual's DNA sequence in the database
    for people in peoplelist:

        # Iterates through each STR sequence to see if the counts (database vs unidentified) match
        matchcount = 0
        for str in strlist:
            if int(people[str]) == int(dnastrcounts[str]):
                matchcount += 1

        # If all STR sequences match, then we have found the individual the DNA sequence belongs to and can print out the name
        if matchcount == strsequencecount:
            print(people["name"])
            break
        
    # If no matches when comparing to the database, then we can print that there is no match
    else:
        print("No match")



# Determines the longest consecutive count of each STR for the unidentified DNA sequence
def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == "__main__":
    main()
