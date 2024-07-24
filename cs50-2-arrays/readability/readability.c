// The 'readability' program allows the user to input an excerpt of text and the program will give the reading grade level
// Grade reading level is based on the Coleman-Liau index formula
// Limitations: No extra ./!/? besides at the end of a sentence and no double spaces (program does not account for these)

#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Gets the user to input an excerpt of text
    string text = get_string("Text: ");

    // Counts and prints the number of letters in the text
    int letters = count_letters(text);
    printf("Letters: %i\n", letters);

    // Counts and prints the number of words in the text
    int words = count_words(text);
    printf("Words: %i\n", words);

    // Counts and prints the number of sentences in the text
    int sentences = count_sentences(text);
    printf("Sentences: %i\n", sentences);

    // Determines 'L' which is the average number of letters per 100 words
    float L = (float) letters / words * 100;

    // Determines 'S' which is the average number of sentences per 100 words
    float S = (float) sentences / words * 100;

    // Determines and rounds to the nearest reading grade level based on Coleman-Liau's formula
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int roundedindex = round(index);

    // Prints the reading grade level
    if (roundedindex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (roundedindex >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", roundedindex);
    }
}


// Counts the number of letters in the text
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}


// Counts the number of words in the text
int count_words(string text)
{
    int count = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return count;
}


// Counts the number of sentences in the text
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}
