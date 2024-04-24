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
            temp[i][j].rgbtBlue = round((float)totalblue/counter);
            temp[i][j].rgbtGreen = round((float)totalgreen/counter);
            temp[i][j].rgbtRed = round((float)totalred/counter);
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


// Detect edges (amplifies the difference)
// Uses the Sobel operator with gx and gy arrays to detect for horizontal and vertical edges (large changes in color values)
    // Gx: {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}
    // Gy: {-1, -2, -1}, {0, 0, 0}, {1, 2, 1}

// Gx/gy is determined for each R/G/B color for each pixel
    // Done by multiplying the surrounding pixels (including pixel itself) by corresponding gx or gy factor (3x3 grid) and then summing them up
// Then sqrt(gx^2 + gx^2) is used to get the value of each R/G/B color for the pixel
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Creates a temporary array to copy the image over
    // If we change the actual image array itself, it will affect the other surrounding pixels when we try to modify them
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Creating a 2D array for the gx/gy 3x3 grids
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Iterating through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Sets all of the color's gx/gy values to 0 so we can sum them up later
            int redgx = 0;
            int redgy = 0;
            int greengx = 0;
            int greengy = 0;
            int bluegx = 0;
            int bluegy = 0;

            // Determines the square of pixels (surrounding and including) the current pixel at [i][j]
            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    int currenth = i + h;
                    int currentw = j + w;

                    // Determines if each pixel in the square of pixels (surrounding and including) are valid (not outside image boundaries)
                    // If valid, can add that pixel to the total gx/gy sum of each color
                    if (currenth >= 0 && currenth <= height - 1 && currentw >= 0 && currentw <= width - 1)
                    {
                        redgx += image[currenth][currentw].rgbtRed * gx[h + 1][w + 1];
                        redgy += image[currenth][currentw].rgbtRed * gy[h + 1][w + 1];
                        greengx += image[currenth][currentw].rgbtGreen * gx[h + 1][w + 1];
                        greengy += image[currenth][currentw].rgbtGreen * gy[h + 1][w + 1];
                        bluegx += image[currenth][currentw].rgbtBlue * gx[h + 1][w + 1];
                        bluegy += image[currenth][currentw].rgbtBlue * gy[h + 1][w + 1];
                    }
                }
            }
            // Determines the color value of the pixel using the gx/gy for each color in a formula sqrt(gx^2 + gx^2)
            int red = round(sqrt((redgx * redgx) + (redgy * redgy)));
            int green = round(sqrt((greengx * greengx) + (greengy * greengy)));
            int blue = round(sqrt((bluegx * bluegx) + (bluegy * bluegy)));

            // Directly changing only the temporary image
            // Changing each pixel to the color value determined and capping the color values at 255 if it is >255
            if (red > 255)
                temp[i][j].rgbtRed = 255;
            else
                temp[i][j].rgbtRed = red;
            if (green > 255)
                temp[i][j].rgbtGreen = 255;
            else
                temp[i][j].rgbtGreen = green;
            if (blue > 255)
                temp[i][j].rgbtBlue = 255;
            else
                temp[i][j].rgbtBlue = blue;
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
