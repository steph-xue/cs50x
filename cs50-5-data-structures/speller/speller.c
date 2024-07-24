// The 'speller' program implements a spell-checker to spell check a text file against a dictionary of choice
// The user can input ./speller [dictionary file] [text file] OR /speller [text file] (default large dictionary will be used)
// The program will load the dictionary of choice (or default dictionary) into a hash table using a hash function to determine the index
// Then it will spell check each word in the text file against the dictionary to determine if it is spelled corrected (matches a dictionary word)
    // Spell checker should be case insensitive (doesn't matter what the case is)
// The program will then determine the size of the dictionary (number of words) and unload all of the memory malloced during the loading process

// Dictionary assumptions:
    // Alphabetically sorted top to bottom; one word per line; each line ends with '\n'
    // Contains at least 1 word; words are no longer than LENGTH; no word appears more than once
    // Word contains only lowercase alphabetical characters and apostrophes; no words starts with apostrophe

// The program will print out:
    // The number of words in the dictionary
    // Number of words in the text
    // Each mispelled word
    // The number of mispelled
    // The time to perform each function (load, check, size, unload)

// Goal: to implement the load, check, size, and unload functions in dictionary.c and maximize efficiency of the functions (performance time)

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "dictionary.h"

// Undefine any definitions
#undef calculate
#undef getrusage

// Define default dictionary
#define DICTIONARY "dictionaries/large"

// Function prototypes
double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char *argv[])
{
    // Check for correct number of command-line arguments (either 2 or 3)
    // User can input ./speller [dictionary file] [text file] OR /speller [text file] (default large dictionary will be used)
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./speller [dictionary file - optional] [text file]\n");
        return 1;
    }

    // Structures for timing data
    struct rusage before, after;

    // Benchmarks for timing data
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

    // Determine dictionary to use (based on if one was inputed as a command-line argument)
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    // Load dictionary into the hash table (& get before and after loading times)
    getrusage(RUSAGE_SELF, &before);
    bool loaded = load(dictionary);
    getrusage(RUSAGE_SELF, &after);

    // Exit if dictionary not loaded
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    // Calculate time to load dictionary (difference between before and after times)
    time_load = calculate(&before, &after);

    // Open text file (based on what was inputed as a command-line argument)
    // If cannot open/locate file, prints out an error message
    char *text = (argc == 3) ? argv[2] : argv[1];
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    // Prepare to report misspellings (header prompt)
    printf("\nMISSPELLED WORDS\n\n");

    // Prepare to spell-check the text file
    // Initialize variables for word index (specifies which character in the word array), number of misspellings, number of words read
    // Initialize variables for the word read (word array) and char c (to add characters to the word being read)
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];
    char c;

    // Spell-check each word in text
    // Goes through each character in the text file
    while (fread(&c, sizeof(char), 1, file))
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word and increment the index
            word[index] = c;
            index++;

            // Ignore alphabetical strings too long to be words (these words are discarded)
            if (index > LENGTH)
            {
                // Consume remainder of alphabetical string (rest of alpha chars are discarded until space/punctuation is reached at end of word)
                while (fread(&c, sizeof(char), 1, file) && isalpha(c));

                // Prepare for new word
                index = 0;
            }
        }

        // Ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // Consume remainder of alphanumeric string (these words with numbers are discarded until space/punctuation is reached at end of word)
            while (fread(&c, sizeof(char), 1, file) && isalnum(c));

            // Prepare for new word
            index = 0;
        }

        // Else the char is not alpha, ', # (e.g. is blank, punctuation, new line) and is not the first char of the word
        // Then we know the word has ended (must have found whole word) and can add a '\0' character to the end
        else if (index > 0)
        {
            // Terminate current word
            word[index] = '\0';

            // Update counter
            words++;

            // Check word's spelling against words in the dictionary hash table (& get before and after checking times)
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);
            getrusage(RUSAGE_SELF, &after);

            // Calculate time to check against dictionary (difference between before and after times)
            time_check += calculate(&before, &after);

            // Print word if misspelled and increment misspelled words
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            // Prepare for next word
            index = 0;
        }
    }

    // Check whether there was an error
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s.\n", text);
        unload();
        return 1;
    }

    // Close text file
    fclose(file);

    // Determine dictionary's size (& get before and after size determination times)
    getrusage(RUSAGE_SELF, &before);
    unsigned int n = size();
    getrusage(RUSAGE_SELF, &after);

    // Calculate time to determine dictionary's size (difference between before and after times)
    time_size = calculate(&before, &after);

    // Unload dictionary (& get before and after unloading times)
    getrusage(RUSAGE_SELF, &before);
    bool unloaded = unload();
    getrusage(RUSAGE_SELF, &after);

    // Abort if dictionary not unloaded
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    // Calculate time to unload dictionary (difference between before and after times)
    time_unload = calculate(&before, &after);

    // Report all benchmarks
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN size:         %.2f\n", time_size);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n",
           time_load + time_check + time_size + time_unload);

    // Success
    return 0;
}

// Returns number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}
