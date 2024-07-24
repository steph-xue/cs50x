// The 'wordle' program is a game where the user tries to guess the word selected by the game within a limited number of attempts (word length + 1 guesses)
// The user can input the word length to guess (between 5-8) as a command-line argument
// A word will be randomly selected (based on length inputed by user) from a list that contains 1000 different words of the same length
// The game will then tell the user to guess the word (in lowercase) and will print out the guess, color coded based on the following below:
    // GREEN means the letter in the guess exactly matches the letter in the target word (same position)
    // YELLOW means the letter in the guess is located somewhere else in the target word (different position)
    // RED means the letter in the guess is not present in the target word
// The user wins if they can guess the word correctly, and loses once they run out of guesses


#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Each of our text files contains 1000 words
#define LISTSIZE 1000

// Values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// User-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{
    // Ensure proper usage (accepts only a single command-line argument wordsize number)
    if (argc != 2)
    {
        printf("./wordle wordsize\n");
        return 1;
    }

    // First defines wordsize as 0 before storing a value
    int wordsize = 0;

    // Ensures argv[1] is either 5, 6, 7, or 8 and stores that value in wordsize instead
    if (atoi(argv[1]) == 5 || atoi(argv[1]) == 6 || atoi(argv[1]) == 7 || atoi(argv[1]) == 8)
    {
        wordsize = atoi(argv[1]);
    }
    else
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;
    }

    // Open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // Load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // Pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // Allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // Print greeting, using ANSI color codes to demonstrate
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // Main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // Obtain user's guess
        string guess = get_guess(wordsize);

        // Array to hold guess status, initially set to zero
        int status[wordsize];

        // Set all elements of status array initially to 0, aka WRONG
        for (int j = 0; j < wordsize; j++)
        {
            status[j] = WRONG;
        }

        // Calculate total score for the guess (letter scores are stored directly in the status array)
            // EXACT (2 points) are assigned to the letter if the letter in the guess exactly matches the letter in the choice (same position)
            // CLOSE (1 point) is assigned if to the letter if the letter in the guess is located somewhere else in the choice (different position)
            // WRONG (0 points) is automatically assigned to the letter as default, and remains as default if the letter in the guess is not present in the choice
        int score = check_word(guess, wordsize, status, choice);

        // Prints the header for the guess, color coded based on scores
        printf("Guess %i: ", i + 1);

        // Prints the guess, color coded based on scores (GREEN = EXACT (2), YELLOW = CLOSE (1), RED = WRONG (0))
        print_word(guess, wordsize, status);

        // If they guessed the word exactly right (guess == choice), set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // Print the game's result based on if the user correctly guessed the word
    if (won == true)
    {
        printf("You won!\n");
    }
    else
    {
        printf("Sorry, you ran out of guesses, the word you were trying to guess is '%s'\n", choice);
    }

    // That's all folks!
    return 0;
}


// Obtain the user's guess and remind them if the guess is not the correct length
string get_guess(int wordsize)
{
    string guess;
    do
    {
        guess = get_string("Input a %i-letter word (lowercase): ", wordsize);
    }
    while (strlen(guess) != wordsize);
    return guess;
}


// Calculate total score for the guess (letter scores are stored directly in the status array)
int check_word(string guess, int wordsize, int status[], string choice)
{
    // Setting the initial score as 0 so we can later add them up
    int score = 0;

    // Iterating over each letter of the guess and comparing it to each letter of the choice to determine a score for each guess letter (stored in status[] array)
        // EXACT (2 points) are assigned to the letter if the letter in the guess exactly matches the letter in the choice (same position)
        // CLOSE (1 point) is assigned if to the letter if the letter in the guess is located somewhere else in the choice (different position)
        // WRONG (0 points) is automatically assigned to the letter as default, and remains as default if the letter in the guess is not present in the choice

    // Iterating over each letter of the guess
    for (int i = 0; i < wordsize; i++)
    {
        // Iterating over each letter of the choice
        for (int j = 0; j < wordsize; j++)
        {
            // When comparing same positions (guess and choice), if the letters match then EXACT (2 points) can be stored for the guess letter
            // Break stops the loop and moves on from comparing the same guess letter (so we can store the highest point value)
            if (i == j)
            {
                if (guess[i] == choice[j])
                {
                    status[i] = EXACT;
                    break;
                }
            }
            // When comparing different positions (guess and choice), if the letters match then CLOSE (1 point) can be stored for the guess letter
            // No break to stop the loop in case guess and choice letter also matches when comparing the same position later (overrides with higher point value)
            else
            {
                if (guess[i] == choice[j])
                {
                    status[i] = CLOSE;
                }
            }

        }
    }

    // Adds up and returns the total score from the sum of all the guess letter scores stored in the status[] array
    for (int k = 0; k < wordsize; k++)
    {
        score = score + status[k];
    }
    return score;
}

// Prints the guess, color coded based on scores (GREEN = EXACT (2), YELLOW = CLOSE (1), RED = WRONG (0))
void print_word(string guess, int wordsize, int status[])
{
    // Goes through each letter in the guess and uses the points in the status[] array to print out the guess letter in the corresponding color based on scores
    for (int i = 0; i < wordsize; i++)
    {
        if (status[i] == EXACT)
        {
            printf(GREEN"%c"RESET"", guess[i]);
        }
        if (status[i] == CLOSE)
        {
            printf(YELLOW"%c"RESET"", guess[i]);
        }
        if (status[i] == WRONG)
        {
            printf(RED"%c"RESET"", guess[i]);
        }
    }
    printf("\n");
}
