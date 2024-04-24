// The 'helper's program changes the black pixels of the smiley image in 'smiley.bmp' to a color of your liking in a new file 'outfile.bmp'
// To execute, type in just 'made' to compile the code, and then './colorize smiley.bmp outfile.bmp' to create a new bmp file with the changes in color
// Only this function needs to be finished, the rest of the files are already pre-made

#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00)
            {
                image[i][j].rgbtRed = 0xD0;
                image[i][j].rgbtGreen = 0x80;
                image[i][j].rgbtBlue = 0xAF;
            }
        }
    }
}
