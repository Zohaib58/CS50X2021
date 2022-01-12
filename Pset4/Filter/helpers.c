#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++) // To control rows/height
    {
        for (int j = 0; j < width; j++) //  To control column/height
        {
            int redPixel = image[i][j].rgbtRed;
            int greenPixel = image[i][j].rgbtGreen;
            int bluePixel = image[i][j].rgbtBlue;

            int avgPixel =  round((redPixel + greenPixel + bluePixel) /
                                  3.0);  // Pixels are added and divided by a floating point value 3.0 to get answer in 'double' which is then rounded to integer
            image[i][j].rgbtRed = avgPixel;
            image[i][j].rgbtGreen = avgPixel;
            image[i][j].rgbtBlue = avgPixel;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    int f_width = width; // Contains the total number of pixels in a row

    width = width % 2 == 1 ? width / 2 + 1 : width /
            2; // if width is odd then store 1 + 0.5width, otherwise store 0.5width in the variable 'width'

    /*

    The following part of the code takes each pixel by using i and j as its index and stores it in the RGBTRIPLE type variable
    'temp'. The respective pixel from the other corner is stored in the pixel of 'i' 'j' index position. The pixel stored in
    'temp' is stored in the pixel from the other corner.

    This is basically sorting the pixels in a row in a reverse order.

    As we reach to atleast half of the row while sorting, the sorting of all the pixels is already performed so we run the loop
    until half/half + 1 of the total pixels in a row.

    */
    for (int i = 0; i < height; i++) // To control rows/height
    {
        for (int j = 0; j < width; j++) // To control column/width
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][(f_width - j) - 1];
            image[i][(f_width - j) - 1] = temp;
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width]; // Creating a copy of image to store changed pixels temporarily to avoid problems for calculation for other pixels

    for (int i = 0; i < height; i++) // To control rows/height
    {
        for (int j = 0; j < width; j++) // To control column/width
        {
            int addRed = 0, addBlue = 0, addGreen = 0;
            float count = 0.0;

            /*
            The following part of the code firstly runs two loops with control variables k and l to fulfil the condition
            of collecting data of pixels within one row and one column of the selected pixel. Therefore, if the pixel is
            at ith row and jth column then the two loops running from i-1 to i+1 and from j-1 to j+1 would ensure that the
            data of pixels forming a 3x3 box, within one row and one column, is collected.
            */
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k >= 0 && k < height) // To check row for the pixels on edge
                    {
                        if (l >= 0 && l < width) // To check column for the pixels on edge
                        {
                            addRed += image[k][l].rgbtRed;
                            addBlue += image[k][l].rgbtBlue;
                            addGreen += image[k][l].rgbtGreen;
                            count++;
                        }
                    }
                }
            }
            // The new pixel is stored in the image2 to not affect the original image
            image2[i][j].rgbtRed = (round)((addRed) / count);
            image2[i][j].rgbtBlue = (round)((addBlue) / count);
            image2[i][j].rgbtGreen = (round)((addGreen) / count);
        }
    }
    /*
    The following part of the code copies the pixels, stored in the copy of image created temporarily, to the original image
    */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image2[i][j].rgbtRed;
            image[i][j].rgbtBlue = image2[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image2[i][j].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width]; // Creating a copy of image to store changed pixels temporarily to avoid problems for calculation for other pixels

    // Declaring/Initialising two matrices containing values to be used to calculated weighted sum
    int Gx[3][3] = {
                   {-1, 0, 1},
                   {-2, 0, 2},
                   {-1, 0, 1},
                   };

    int Gy[3][3] = {
                   {-1, -2, -1},
                   {0, 0, 0},
                   {1, 2, 1},
                   };



    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Rx, Ry, Grx, Gry, Bx, By;
            Rx = Ry = Grx = Gry = Bx = By = 0;


            /*

            The following part of the code fulfills major chunk of requirements:

            1. Loops are running from -1 to 1 and the pixels of the image would be called by adding i and j to k and l respectively
               which would again ensure that all the pixels within one row and one column forming 3x3 matrix are used in the
               calculation.

            2. The values stored in the Gx and Gy matrix to calculate the weighted sum are called by adding 1 to k and l. This would
               ensure coherence in calculation as when k & l = -1 we need to multiply with the value at Zero th index of the Gx & Gy
               array, thus we would add 1 to 'k' & 'l' of the respective array's indexes while calling.

            */
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + k >= 0 && i + k < height) // To check row for the pixels on edge
                    {
                        if (j + l >= 0 && j + l < width) // To check column for the pixels on edge
                        {
                           Rx += image[k + i][l + j].rgbtRed * Gx[k + 1][l + 1];
                           Ry += image[k + i][l + j].rgbtRed * Gy[k + 1][l + 1];

                           Grx += image[k + i][l + j].rgbtGreen * Gx[k + 1][l + 1];
                           Gry += image[k + i][l + j].rgbtGreen * Gy[k + 1][l + 1];

                           Bx += image[k + i][l + j].rgbtBlue * Gx[k + 1][l + 1];
                           By += image[k + i][l + j].rgbtBlue * Gy[k + 1][l + 1];
                        }
                    }
                }
            }
            int RG = round(sqrt((Rx * Rx) + (Ry * Ry)));
            RG = RG > 255 ? 255 : RG; // If RG is greater than 255, store 255 in RG. Else store the same value.
            int GG = round(sqrt((Grx * Grx) + (Gry * Gry)));
            GG = GG > 255 ? 255 : GG; // If GG is greater than 255, store 255 in GG. Else store the same value.
            int BG = round(sqrt((Bx * Bx) + (By * By)));
            BG = BG > 255 ? 255 : BG; // If BG is greater than 255, store 255 in BG. Else store the same value.



            // The new pixel is stored in the image2 to not affect the original image
            image2[i][j].rgbtRed = RG;
            image2[i][j].rgbtBlue = BG;
            image2[i][j].rgbtGreen = GG;
        }
    }
    /*
    The following part of the code copies the pixels stored in the copy of image created temporarily to the original image
    */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image2[i][j].rgbtRed;
            image[i][j].rgbtBlue = image2[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image2[i][j].rgbtGreen;
        }
    }
    return;
}
