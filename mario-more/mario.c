#include <cs50.h>
#include <stdio.h>
#include <math.h>

//int height (int n)
    //{
        //return (pow(2,n));
    //}


int main(void)
{

    int rows = 0;

    do
    {
        rows = get_int("Choose a Number Between 1 and 8: ");
    }

    while (rows < 1 || rows > 8);

    int hashes_per_line = rows + 1;
    int number_of_characters_per_row =  (2 * hashes_per_line) - 1;

    int hashes_per_line_in_row = 2;
    int dots_per_line_per_row_total = rows - 1;


    for (int i = 1; i <= rows; i++)
    {

            int hashes_per_line_in_loop = 0;
            int dots_per_line_per_row = 0;

            //int dots_per_line_in_loop = 0;
            //int dots_per_line_in_loop_total = 0;

             //number of characters on a line
            for (int j = 1; j <= number_of_characters_per_row; j++)
            {

                //print f number of dots until dots = rows -1
                //meanwhile print f #
                //then when # equals row print f dot dot and start hash tags back at zero/1
                //print f number of hash tags until hash tags  = row


                 if(dots_per_line_per_row < dots_per_line_per_row_total)
                    {
                    printf(" ");
                    dots_per_line_per_row++;
                    }

                 else if(hashes_per_line_in_loop + hashes_per_line_in_loop == hashes_per_line_in_row)
                    {
                    printf("  ");
                    hashes_per_line_in_loop++;
                    }

                 else if(hashes_per_line_in_loop <= hashes_per_line_in_row)
                    {
                    printf("#");
                    hashes_per_line_in_loop++;
                    }

                 //else {
                    //printf(" ");
                    //hashes_per_line_in_loop++;
                  //}

            }

            hashes_per_line_in_row += 2;
            dots_per_line_per_row_total -= 1;
            //printf("%i", hashes_per_line_in_row);
            printf("\n");

    }

}
