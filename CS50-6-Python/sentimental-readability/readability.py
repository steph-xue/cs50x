# The 'readability' program allows the user to input an excerpt of text and the program will give the reading grade level
# Grade reading level is based on the Coleman-Liau index formula
# Limitations: No extra ./!/? besides at the end of a sentence and no double spaces (program does not account for these)


def main():

    # Prompt the user for some text
    text = input("Text: ").strip()

    # Count the number of letters in the text
    letters = count_letters(text)

    # Count the number of words in the text
    words = count_words(text)

    # Count the number of sentences in the text
    sentences = count_sentences(text)

    # Compute the Coleman-Liau index
    L = letters / words * 100
    S = sentences / words * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Prints the reading grade level
    if index < 1:
        print("Before Grade 1")
    elif 1 <= index < 16:
        print(f"Grade {index}")
    else:
        print("Grade 16+")


# Count the number of letters in the text
def count_letters(text):
    count = 0
    for c in text:
        if c.isalpha():
            count += 1
    return count


# Count the number of words in the text
def count_words(text):
    count = 1
    for c in text:
        if c.isspace():
            count += 1
    return count


# Count the number of sentences in the text
def count_sentences(text):
    count = 0
    for c in text:
        if c in [".", "!", "?"]:
            count += 1
    return count


if __name__ == "__main__":
    main()
