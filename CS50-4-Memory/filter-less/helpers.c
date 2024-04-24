// Program's functions
// The problem set involves making the functions to add different filters to the images depending on the user's input

#include "helpers.h"
#include <math.h>

// Convert image to grayscale
// Greyscale involves all the blue/green/red colors being of the same value and the shade is dependent on the value itself
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterating through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculates the average of each pixel's blue, green, and red colors and sets each color to the same average value
            BYTE average = round(((float) image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average;
        }
    }
    return;
}


// Convert image to sepia
// A formula for each color (R/B/G) can be used to determine the modified sepia value of each color for each pixel (cap the max values at 255)
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterating through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Uses the sepia formula for each color to determine the sepia R/G/B color value for each pixel
            int sepiaBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));
            int sepiaGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            int sepiaRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));

            // Sets the max sepia color value at 255 if it is >255 (the formula can yield values higher than 255)
            if (sepiaBlue > 255)
                image[i][j].rgbtBlue = 255;
            else
                image[i][j].rgbtBlue = (BYTE) sepiaBlue;

            if (sepiaGreen > 255)
                image[i][j].rgbtGreen = 255;
            else
                image[i][j].rgbtGreen = (BYTE) sepiaGreen;

            if (sepiaRed > 255)
                image[i][j].rgbtRed = 255;
            else
                image[i][j].rgbtRed = (BYTE) sepiaRed;
         }
    }
    return;
}


// Reflect image horizontally
// Can swap the pixels without needing to modify the values of the R/G/B pixels
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create buffer for swapping
    RGBTRIPLE buffer;

    // Iterating through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        // Goes through each column till the middle and swaps the left pixel with the corresponding right pixel
        for (int j = 0; j < width/2; j++)
        {
            buffer = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = buffer;
        }
    }
    return;
}


// Blur image
// The average of the color values (R/G/B) of a pixel and its surrounding pixels (square border) determines the pixel's 'blurred' color value
// Invalid pixels (outside of the image boundaries) are not counted towards the average
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Creates a temporary array to copy the image over
    // If we change the actual image array itself, it will affect the other surrounding pixels when we try to blur them
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Iterating through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // For each pixel, sets the total values for R/G/B and the counter for the number of total valid pixels to 0 (pixel plus surroundings)
            // This is then used to calculate the average of each of the color values for the pixel plus surroundings to blur the pixel
            int totalblue, totalgreen, totalred;
            totalblue = totalgreen = totalred = 0;
            int counter = 0;

            // Determines the square of pixels (surrounding and including) the current pixel at [i][j]
            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    int currenth = i + h;
                    int currentw = j + w;

                    // Determines if each pixel in the square of pixels (surrounding and including) are valid (not outside image boundaries)
                    // If valid, can add that pixel to the total color value and counter of valid pixels
                    if (currenth >= 0 && currenth <= height - 1 && currentw >= 0 && currentw <= width - 1)
                    {
                        totalblue += image[currenth][currentw].rgbtBlue;
                        totalgreen += image[currenth][currentw].rgbtGreen;
                        totalred += image[currenth][currentw].rgbtRed;
                        counter++;
                    }
                 }
            }
            // Determines the average R/G/B color values of all the pixels (surroudings and including itself) with the count of valid pixels
            // Directly changing only the temporary image
            temp[i][j].rgbtBlue = round(totalblue/counter);
            temp[i][j].rgbtGreen = round(totalgreen/counter);
            temp[i][j].rgbtRed = round(totalred/counter);
        }
    }

    // Then the modified temporary image can be copied over to the actual image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
