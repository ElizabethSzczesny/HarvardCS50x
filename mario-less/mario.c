#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int rows = 0;

    do
    {
        rows = get_int("Choose a Number Between 1 and 8: ");
    }
    while (rows < 1 || rows > 8);

        int dots = rows;

        for (int i = 1; i <= rows; i++)
        {

            int hashes = 1;

            for (int j = 1; j <= rows  ; j++)
            {

                if ( dots <= hashes )
                    {
                    printf("#");
                    hashes++;
                    }
                 else      {
                    printf(" ");
                    hashes++;
                }
             }

            dots--;
            printf("\n");

            //printf("%i", hashes);
            //printf("%i", dots);

        }

}
