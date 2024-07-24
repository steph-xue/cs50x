# The 'speller' program (cannot actually run) shows the syntax of the 'speller' spell check program if it was written in python instead of C

# Load up the dictionary file of choice into a hash table
def load(dictionary):

    # Automatically creates hash table using set()
    # dict() can be used if you need keys and value (e.g. words and definitions)
    words = set()

    # Open up the dictionary file
    file = open(dictionary, "r")

    # Add each line from the dictionary into the words hash table (after striping the '\n' in each line)
    for line in file:
        word = line.rstrip()
        words.add(word)
    close(file)
    return True


# Check to see if the word is in the dictionary
def check(word):
    if word.lower() in words:
        return True
    else:
        return False


# Determine the number of words in the dictionary
# Can use len() to calculate the number of items
def size(dictionary):
    return len(words)


# Free up memory allocated
# In python, the memory does not need to be manually allocated or freed
def unload():
    return True
