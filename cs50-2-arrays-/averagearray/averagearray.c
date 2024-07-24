// The "averagearray" program allows the user to input the number of test scores and each separate test score to calculate the average

#include <cs50.h>
#include <stdio.h>

float average(int N, int score[]);

int main(void)
{
    // Getting N number of scores from the user
    int N;
    do
    {
        N = get_int("How many scores?: ");
    }
    while (N < 1);

    // Getting scores from the user based on N number of scores
    int score[N];
    for (int i = 0; i < N; i++)
    {
        score[i] = get_int("What is the score?: ");
    }

    // Calculate and print the average based on N number of scores
    printf("The average is: %0.2f\n", average(N, score));
}

// Calcuate the average based on N number of scores
float average(int N, int score[])
{
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += score[i];
    }
    return sum / (float) N;
}
