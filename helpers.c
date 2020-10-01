#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float graysc = (float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float) 3 ;
            image[i][j].rgbtBlue = graysc;
            image[i][j].rgbtGreen = graysc;
            image[i][j].rgbtRed = graysc;
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

            float sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            float sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            float sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            do
            {
                if (sepiaRed > 255)
                {
                    sepiaRed = 255;
                }
                else if (sepiaGreen > 255)
                {
                    sepiaGreen = 255;
                }
                else if (sepiaBlue > 255)
                {
                    sepiaBlue = 255;
                }
            }
            while ((sepiaRed > 255) || (sepiaGreen > 255) || (sepiaBlue > 255));

            image[i][j].rgbtBlue = sepiaBlue ;
            image[i][j].rgbtGreen = sepiaGreen ;
            image[i][j].rgbtRed = sepiaRed ;


        }
    }
    return;
}



// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE oimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            oimage[i][j] = image[i][j];
        }
    }
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            float sumRed, sumGreen, sumBlue;
            if (k == 0 && l == 0)
            {
                sumRed = oimage[k][l].rgbtRed + oimage[k][l + 1].rgbtRed + oimage[k + 1][l].rgbtRed + 
                         oimage[k + 1][l + 1].rgbtRed;
                         
                sumBlue = oimage[k][l].rgbtBlue + oimage[k][l + 1].rgbtBlue + oimage[k + 1][l].rgbtBlue +
                          oimage[k + 1][l + 1].rgbtBlue;
                          
                sumGreen = oimage[k][l].rgbtGreen + oimage[k][l + 1].rgbtGreen + oimage[k + 1][l].rgbtGreen +
                           oimage[k + 1][l + 1].rgbtGreen;
                
                image[k][l].rgbtRed = round(sumRed / 4);
                image[k][l].rgbtBlue = round(sumBlue / 4);
                image[k][l].rgbtGreen = round(sumGreen / 4);
            }
            else if (k == 0 && l == (width - 1))
            {
                sumRed = oimage[k][l].rgbtRed + oimage[k][l - 1].rgbtRed + oimage[k + 1][l].rgbtRed +
                         oimage[k + 1][l - 1].rgbtRed;
                         
                sumBlue = oimage[k][l].rgbtBlue + oimage[k][l - 1].rgbtBlue + oimage[k + 1][l].rgbtBlue +
                          oimage[k + 1][l - 1].rgbtBlue;
                          
                sumGreen = oimage[k][l].rgbtGreen + oimage[k][l - 1].rgbtGreen + oimage[k + 1][l].rgbtGreen +
                           oimage[k + 1][l - 1].rgbtGreen;
                
                image[k][l].rgbtRed = round(sumRed / 4);
                image[k][l].rgbtBlue = round(sumBlue / 4);
                image[k][l].rgbtGreen = round(sumGreen / 4);
            }
            else if (k == (height - 1) && l == 0)
            {
                sumRed = oimage[k][l].rgbtRed + oimage[k][l + 1].rgbtRed + oimage[k - 1][l].rgbtRed + 
                         oimage[k - 1][l + 1].rgbtRed;
                         
                sumBlue = oimage[k][l].rgbtBlue + oimage[k][l + 1].rgbtBlue + oimage[k - 1][l].rgbtBlue +
                          oimage[k - 1][l + 1].rgbtBlue;
                          
                sumGreen = oimage[k][l].rgbtGreen + oimage[k][l + 1].rgbtGreen + oimage[k - 1][l].rgbtGreen +
                           oimage[k - 1][l + 1].rgbtGreen;
                
                image[k][l].rgbtRed = round(sumRed / 4);
                image[k][l].rgbtBlue = round(sumBlue / 4);
                image[k][l].rgbtGreen = round(sumGreen / 4);
            }
            else if (k == (height - 1) && l == (width - 1))
            {
                sumRed = oimage[k][l].rgbtRed + oimage[k - 1][l].rgbtRed + oimage[k - 1][l - 1].rgbtRed +
                         oimage[k][l - 1].rgbtRed;
                         
                sumBlue = oimage[k][l].rgbtBlue + oimage[k - 1][l].rgbtBlue + oimage[k - 1][l - 1].rgbtBlue +
                          oimage[k][l - 1].rgbtBlue;
                          
                sumGreen = oimage[k][l].rgbtGreen + oimage[k - 1][l].rgbtGreen + oimage[k - 1][l - 1].rgbtGreen + 
                           oimage[k][l - 1].rgbtGreen;
                
                image[k][l].rgbtRed = round(sumRed / 4);
                image[k][l].rgbtBlue = round(sumBlue / 4);
                image[k][l].rgbtGreen = round(sumGreen / 4);
            }
            else if (k == 0)
            {
                sumRed = oimage[k][l].rgbtRed + oimage[k][l - 1].rgbtRed + oimage[k + 1][l - 1].rgbtRed +
                         oimage[k + 1][l].rgbtRed + oimage[k + 1][l + 1].rgbtRed + oimage[k][l + 1].rgbtRed;
                         
                sumBlue = oimage[k][l].rgbtBlue + oimage[k][l - 1].rgbtBlue + oimage[k + 1][l - 1].rgbtBlue +
                          oimage[k + 1][l].rgbtBlue + oimage[k + 1][l + 1].rgbtBlue + oimage[k][l + 1].rgbtBlue;
                          
                sumGreen = oimage[k][l].rgbtGreen + oimage[k][l - 1].rgbtGreen + oimage[k + 1][l - 1].rgbtGreen +
                           oimage[k + 1][l].rgbtGreen + oimage[k + 1][l + 1].rgbtGreen + oimage[k][l + 1].rgbtGreen;
                
                image[k][l].rgbtRed = round(sumRed / 6);
                image[k][l].rgbtBlue = round(sumBlue / 6);
                image[k][l].rgbtGreen = round(sumGreen / 6);
            }
            else if (k == height - 1)
            {
                sumRed = oimage[k][l].rgbtRed + oimage[k][l - 1].rgbtRed + oimage[k - 1][l - 1].rgbtRed +
                         oimage[k - 1][l].rgbtRed + oimage[k][l + 1].rgbtRed + oimage[k - 1][l + 1].rgbtRed;
                         
                sumBlue = oimage[k][l].rgbtBlue + oimage[k][l - 1].rgbtBlue + oimage[k - 1][l - 1].rgbtBlue +
                          oimage[k - 1][l].rgbtBlue + oimage[k][l + 1].rgbtBlue + oimage[k - 1][l + 1].rgbtBlue;
                          
                sumGreen = oimage[k][l].rgbtGreen + oimage[k][l - 1].rgbtGreen + oimage[k - 1][l - 1].rgbtGreen +
                           oimage[k - 1][l].rgbtGreen + oimage[k][l + 1].rgbtGreen + oimage[k - 1][l + 1].rgbtGreen;
                
                image[k][l].rgbtRed = round(sumRed / 6);
                image[k][l].rgbtBlue = round(sumBlue / 6);
                image[k][l].rgbtGreen = round(sumGreen / 6);
            }
            else if (l == 0)
            {
                sumRed = oimage[k][l].rgbtRed + oimage[k][l + 1].rgbtRed + oimage[k - 1][l + 1].rgbtRed +
                         oimage[k - 1][l].rgbtRed + oimage[k + 1][l + 1].rgbtRed + oimage[k + 1][l].rgbtRed;
                         
                sumBlue = oimage[k][l].rgbtBlue + oimage[k][l + 1].rgbtBlue + oimage[k - 1][l + 1].rgbtBlue +
                          oimage[k - 1][l].rgbtBlue + oimage[k + 1][l + 1].rgbtBlue + oimage[k + 1][l].rgbtBlue;
                          
                sumGreen = oimage[k][l].rgbtGreen + oimage[k][l + 1].rgbtGreen + oimage[k - 1][l + 1].rgbtGreen + 
                           oimage[k - 1][l].rgbtGreen + oimage[k + 1][l + 1].rgbtGreen + oimage[k + 1][l].rgbtGreen;
                
                image[k][l].rgbtRed = round(sumRed / 6);
                image[k][l].rgbtBlue = round(sumBlue / 6);
                image[k][l].rgbtGreen = round(sumGreen / 6);
            }
            else if (l == width - 1)
            {
                sumRed = oimage[k][l].rgbtRed + oimage[k][l - 1].rgbtRed + oimage[k - 1][l - 1].rgbtRed +
                         oimage[k - 1][l].rgbtRed + oimage[k + 1][l - 1].rgbtRed + oimage[k + 1][l].rgbtRed;
                         
                sumBlue = oimage[k][l].rgbtBlue + oimage[k][l - 1].rgbtBlue + oimage[k - 1][l - 1].rgbtBlue +
                          oimage[k - 1][l].rgbtBlue + oimage[k + 1][l - 1].rgbtBlue + oimage[k + 1][l].rgbtBlue;
                          
                sumGreen = oimage[k][l].rgbtGreen + oimage[k][l - 1].rgbtGreen + oimage[k - 1][l - 1].rgbtGreen +
                           oimage[k - 1][l].rgbtGreen + oimage[k + 1][l - 1].rgbtGreen + oimage[k + 1][l].rgbtGreen;
                
                image[k][l].rgbtRed = round(sumRed / 6);
                image[k][l].rgbtBlue = round(sumBlue / 6);
                image[k][l].rgbtGreen = round(sumGreen / 6);
            }
            else
            {
                sumRed = oimage[k - 1] [l + 1].rgbtRed + // Top left
                         oimage[k + 0][l + 1].rgbtRed + // Top center
                         oimage[k + 1] [l + 1].rgbtRed + // Top right
                         oimage[k - 1] [l + 0].rgbtRed + // Mid left
                         oimage[k + 0] [l + 0].rgbtRed + // Current pixel
                         oimage[k + 1] [l + 0].rgbtRed + // Mid right
                         oimage[k - 1] [l - 1].rgbtRed + // Low left
                         oimage[k + 0] [l - 1].rgbtRed + // Low center
                         oimage[k + 1] [l - 1].rgbtRed;  // Low right


                sumGreen = oimage[k - 1] [l + 1].rgbtGreen + // Top left
                           oimage[k + 0][l + 1].rgbtGreen + // Top center
                           oimage[k + 1] [l + 1].rgbtGreen + // Top right
                           oimage[k - 1] [l + 0].rgbtGreen + // Mid left
                           oimage[k + 0] [l + 0].rgbtGreen + // Current pixel
                           oimage[k + 1] [l + 0].rgbtGreen + // Mid right
                           oimage[k - 1] [l - 1].rgbtGreen + // Low left
                           oimage[k + 0] [l - 1].rgbtGreen + // Low center
                           oimage[k + 1] [l - 1].rgbtGreen;  // Low right

                sumBlue = oimage[k - 1] [l + 1].rgbtBlue + // Top left
                          oimage[k + 0][l + 1].rgbtBlue + // Top center
                          oimage[k + 1] [l + 1].rgbtBlue + // Top right
                          oimage[k - 1] [l + 0].rgbtBlue + // Mid left
                          oimage[k + 0] [l + 0].rgbtBlue + // Current pixel
                          oimage[k + 1] [l + 0].rgbtBlue + // Mid right
                          oimage[k - 1] [l - 1].rgbtBlue + // Low left
                          oimage[k + 0] [l - 1].rgbtBlue + // Low center
                          oimage[k + 1] [l - 1].rgbtBlue;  // Low right

                image[k][l].rgbtRed = round(sumRed / 9);
                image[k][l].rgbtBlue = round(sumBlue / 9);
                image[k][l].rgbtGreen = round(sumGreen / 9);
            }


        }
    }

    return;
}
