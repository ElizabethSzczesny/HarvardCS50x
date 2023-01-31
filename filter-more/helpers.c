#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float pixelcolor = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0;
            image[i][j].rgbtRed = round(pixelcolor);
            image[i][j].rgbtGreen = round(pixelcolor);
            image[i][j].rgbtBlue = round(pixelcolor);
        }
    }
    return;
}

//Swap function for reflecting image horizontally
/*
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
RGBTRIPLE tmp = *a;
*a = *b;
*b = tmp;
}
*/

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
      for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

RGBTRIPLE copy[height][width];
for(int i = 0; i < height; i++)
{
    for (int j = 0; j < width; j++)
    {
        copy[i][j] = image[i][j];
    }
}

    for(int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
        {
            float sumrgbtRED = 0;
            float sumrgbtGREEN = 0;
            float sumrgbtBLUE = 0;
            float directioncount = 0;

                for(int k = -1; k < 2; k++)
                {
                    for (int l = -1; l < 2; l++)
                    {
                        //if( ((i + k) + (j + l)) >= 0 && ((i + k) + (j + l)) < width  && ((i + k) + (j + l)) < height )
                        if( (i + k) >= 0 && (i + k) < height  && (j + l) >= 0 && (j + l) < width)
                        {
                            sumrgbtRED += (float) copy[i + k][j + l].rgbtRed;
                            sumrgbtGREEN += (float) copy[i + k][j + l].rgbtGreen;
                            sumrgbtBLUE += (float) copy[i + k][j + l].rgbtBlue;
                            directioncount += 1.0;
                        }
                    }
                }

            float totalsumrgbtRED = (float) sumrgbtRED/directioncount;
            float totalsumrgbtGREEN = (float) sumrgbtGREEN/directioncount;
            float totalsumrgbtBLUE = (float) sumrgbtBLUE/directioncount;

            image[i][j].rgbtRed = round(totalsumrgbtRED);
            image[i][j].rgbtGreen = round(totalsumrgbtGREEN);
            image[i][j].rgbtBlue = round(totalsumrgbtBLUE);
        }
    }
    return;
}

//you might be re-visiting the same square over and over and it may be one you have already re-written with a new VALUE already, not the original value it started with (which you need)

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

RGBTRIPLE copy[height][width];
for(int i = 0; i < height; i++)
{
    for (int j = 0; j < width; j++)
    {
        copy[i][j] = image[i][j];
    }
}

    for(int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
        {
            long sumrgbtREDx = 0;
            long sumrgbtGREENx = 0;
            long sumrgbtBLUEx = 0;

            long sumrgbtREDy = 0;
            long sumrgbtGREENy = 0;
            long sumrgbtBLUEy = 0;

                //weighted sum in the x and y direction, take each value in the 3x3 square surrounding the pixel
                //and multiply it with the right corresponding number, then add all those values together
                for(int k = -1; k < 2; k++)
                {
                    for (int l = -1; l < 2; l++)
                    {
                        //checks for edge cases and assigns them rgb value of 0
                        if( (i + k) < 0 || (i + k) > height - 1 || (j + l) < 0 || (j + l) > width - 1)
                        {
                            /*sumrgbtREDx += 0;
                            sumrgbtGREENx += 0;
                            sumrgbtBLUEx += 0;
                            sumrgbtREDy += 0;
                            sumrgbtGREENy += 0;
                            sumrgbtBLUEy += 0;*/
                            continue;
                        }
                        else
                        {
                        //for k you can multiply it by l for two of the rows
                            if (k == -1 || k == 1)
                            {
                                sumrgbtREDx += l * (copy[i + k][j + l].rgbtRed);
                                sumrgbtGREENx += l * (copy[i + k][j + l].rgbtGreen);
                                sumrgbtBLUEx += l * (copy[i + k][j + l].rgbtBlue);
                                //printf("%i:copy[i + k][j + l].rgbtRed,%i:i, %i:j, %i:k, %i:l \n",copy[i + k][j + l].rgbtRed,i,j,k,l);
                                //printf("%li:sumrgbtREDx, %i:l wtf\n", sumrgbtREDx, l);
                            }
                            //if k == 0 you multiply it by l + l
                            else if(k == 0)
                            {
                                sumrgbtREDx += (l + l) * (copy[i + k][j + l].rgbtRed);
                                sumrgbtGREENx += (l + l) * (copy[i + k][j + l].rgbtGreen);
                                sumrgbtBLUEx += (l + l) * (copy[i + k][j + l].rgbtBlue);
                                //printf("%i:copy[i + k][j + l].rgbtRed,%i:i, %i:j, %i:k, %i:l \n",copy[i + k][j + l].rgbtRed,i,j,k,l);
                                //printf("%li:sumrgbtREDx, %i:l + l\n", sumrgbtREDx, l);
                            }
                            //for l you can multiply it by k for two of the rows
                            if (l == -1 || l == 1)
                            {
                                sumrgbtREDy += k * (copy[i + k][j + l].rgbtRed);
                                sumrgbtGREENy += k * (copy[i + k][j + l].rgbtGreen);
                                sumrgbtBLUEy += k * (copy[i + k][j + l].rgbtBlue);
                                //printf("%i:copy[i + k][j + l].rgbtRed,%i:i, %i:j, %i:k, %i:l \n",copy[i + k][j + l].rgbtRed,i,j,k,l);
                                //printf("%li:sumrgbtREDy\n", sumrgbtREDy);
                            }
                            //if l == 0 you multiply it by k + k
                            else if(l == 0)
                            {
                                sumrgbtREDy += (k + k) * (copy[i + k][j + l].rgbtRed);
                                sumrgbtGREENy += (k + k) * (copy[i + k][j + l].rgbtGreen);
                                sumrgbtBLUEy += (k + k) * (copy[i + k][j + l].rgbtBlue);
                                //printf("%i:copy[i + k][j + l].rgbtRed,%i:i, %i:j, %i:k, %i:l \n",copy[i + k][j + l].rgbtRed,i,j,k,l);
                                //printf("%li:sumrgbtREDy\n", sumrgbtREDy);
                            }
                        }
                    }
                }

            //The Sobel filter algorithm combines Gx and Gy into a final value by calculating the square root of Gx^2 + Gy^2
            //And since channel values can only take on integer values from 0 to 255, be sure the resulting value is rounded to the nearest integer and capped at 255
            //printf("%li:sumrgbtREDx, %li:sumrgbtREDy\n", sumrgbtREDx, sumrgbtREDy);
            double tempImagergbtRed = pow((double)sumrgbtREDx, 2) + pow((double)sumrgbtREDy, 2);
            double tempImagergbtRedtwo = sqrt(tempImagergbtRed);
            double tempImagergbtRedfinal = round(tempImagergbtRedtwo);
            //printf("%li:tempImagergbtRed", tempImagergbtRed);

            double tempImagergbtGreen = pow((double)sumrgbtGREENx, 2) + pow((double)sumrgbtGREENy, 2);
            double tempImagergbtGreentwo = sqrt(tempImagergbtGreen);
            double tempImagergbtGreenfinal = round(tempImagergbtGreentwo);

            double tempImagergbtBlue = pow((double)sumrgbtBLUEx, 2) + pow((double)sumrgbtBLUEy, 2);
            double tempImagergbtBluetwo = sqrt(tempImagergbtBlue);
            double tempImagergbtBluefinal = round(tempImagergbtBluetwo);

            /*double tempImagergbtRed = round( sqrt( pow(sumrgbtREDx, 2) + pow(sumrgbtREDy, 2) ) );
            double tempImagergbtGreen = round( sqrt( pow(sumrgbtGREENx, 2) + pow(sumrgbtGREENy, 2) ) );
            double tempImagergbtBlue = round( sqrt( pow(sumrgbtBLUEx, 2) + pow(sumrgbtBLUEy, 2) ) );*/

            if(tempImagergbtRedfinal > 255)
            {
                tempImagergbtRedfinal = 255;
            }
            if(tempImagergbtGreenfinal > 255)
            {
                tempImagergbtGreenfinal = 255;
            }
            if(tempImagergbtBluefinal > 255)
            {
                tempImagergbtBluefinal = 255;
            }
            image[i][j].rgbtRed = tempImagergbtRedfinal;
            image[i][j].rgbtGreen = tempImagergbtGreenfinal;
            image[i][j].rgbtBlue = tempImagergbtBluefinal;
        }
    }
    return;
}

