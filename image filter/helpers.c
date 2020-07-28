#include "helpers.h"
#include <math.h>

/**
 *
 * @author HimelSaha
 */


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round(((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)) / 3);

            // setting same average RGB value to all pixels
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE red = image[i][j].rgbtRed;
            BYTE green = image[i][j].rgbtGreen;
            BYTE blue = image[i][j].rgbtBlue;

            // conversion algorithm for sepia effect
            int rgbtRed = round(.393 * red + .769 * green + .189 * blue);
            int rgbtGreen = round(.349 * red + .686 * green + .168 * blue);
            int rgbtBlue = round(.272 * red + .534 * green + .131 * blue);

            // rounding higher values to a max of 255
            if (rgbtRed > 255)
            {
                rgbtRed = 255;
            }
            if (rgbtGreen > 255)
            {
                rgbtGreen = 255;
            }
            if (rgbtBlue > 255)
            {
                rgbtBlue = 255;
            }

            // assigning new values to each pixel
            image[i][j].rgbtRed = rgbtRed;
            image[i][j].rgbtGreen = rgbtGreen;
            image[i][j].rgbtBlue = rgbtBlue;

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        // iteration stops before halfway for reflection effect
        for (int j = 0; j < (width / 2); j++)
        {
            // swapping the RGB values of one pixel to its symmetrically (vertical axis) opposite one
            RGBTRIPLE x = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = x;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_img[height][width];

    for (int i = 0; i < height; i++)    // iterating through every pixel
    {
        for (int j = 0; j < width; j++)
        {
            float totalRed = 0.0;
            float totalGreen = 0.0;
            float totalBlue = 0.0;

            int counter = 0;

            if ((i - 1) >= 0)                                   // if current pixel has pixels on the row above it
            {
                //own pixel
                totalRed += image[i - 1][j].rgbtRed;
                totalGreen += image[i - 1][j].rgbtGreen;
                totalBlue += image[i - 1][j].rgbtBlue;
                counter++;

                if (((j + 1) <= (width - 1)))
                {
                    totalRed += image[i - 1][j + 1].rgbtRed;
                    totalGreen += image[i - 1][j + 1].rgbtGreen;
                    totalBlue += image[i - 1][j + 1].rgbtBlue;
                    counter++;
                }
                if ((j - 1) <= (width - 1) && !((j - 1) < 0))
                {
                    totalRed += image[i - 1][j - 1].rgbtRed;
                    totalGreen += image[i - 1][j - 1].rgbtGreen;
                    totalBlue += image[i - 1][j - 1].rgbtBlue;
                    counter++;
                }

            }

            // the current pixel
            totalRed += image[i][j].rgbtRed;
            totalGreen += image[i][j].rgbtGreen;
            totalBlue += image[i][j].rgbtBlue;
            counter++;

            if (((j + 1) <= (width - 1)))                       // if current pixel has pixel on its right
            {
                totalRed += image[i][j + 1].rgbtRed;
                totalGreen += image[i][j + 1].rgbtGreen;
                totalBlue += image[i][j + 1].rgbtBlue;
                counter++;
            }
            if ((j - 1) <= (width - 1) && !((j - 1) < 0))       // if current pixel has pixel on its right
            {
                totalRed += image[i][j - 1].rgbtRed;
                totalGreen += image[i][j - 1].rgbtGreen;
                totalBlue += image[i][j - 1].rgbtBlue;
                counter++;
            }

            if ((i + 1) <= (height - 1))                        // if current pixel has pixels on the row below it
            {
                //own pixel
                totalRed += image[i + 1][j].rgbtRed;
                totalGreen += image[i + 1][j].rgbtGreen;
                totalBlue += image[i + 1][j].rgbtBlue;
                counter++;

                if (((j + 1) <= (width - 1)) /*&& !((j + 1) < 0)*/)
                {
                    totalRed += image[i + 1][j + 1].rgbtRed;
                    totalGreen += image[i + 1][j + 1].rgbtGreen;
                    totalBlue += image[i + 1][j + 1].rgbtBlue;
                    counter++;
                }
                if ((j - 1) <= (width - 1) && !((j - 1) < 0))
                {
                    totalRed += image[i + 1][j - 1].rgbtRed;
                    totalGreen += image[i + 1][j - 1].rgbtGreen;
                    totalBlue += image[i + 1][j - 1].rgbtBlue;
                    counter++;
                }
            }

            temp_img[i][j].rgbtBlue = round(totalBlue / counter);       // storing the pixels with new RGB values in a new image
            temp_img[i][j].rgbtRed = round(totalRed / counter);
            temp_img[i][j].rgbtGreen = round(totalGreen / counter);

        }
    }

    for (int i = 0; i < height; i++)                                    // copying contents of new image to the original image
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp_img[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp_img[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp_img[i][j].rgbtRed;
        }
    }


    return;
}
