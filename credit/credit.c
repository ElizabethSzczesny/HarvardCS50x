#include <cs50.h>
#include <stdio.h>
#include <math.h>


/*int count = 0;
//original math before checksum turned into one function to get individual digits
void getIndividualDigit(long input_num, double input_num_count) {
    for ( int i = 1; input_num_count > 1; i++ )
    {
        long x = pow(10,i);
        double remainder = input_num % x ;
        double digit_test = (remainder/x) * 10;
        int current_digit = floor(digit_test);
        input_num_count = input_num_count/10;
        count++;
    }
}
//turned into two functions, one for count
int getIndividualCount(double input_num_count) {
    for ( int i = 1; input_num_count > 1; i++ )
    {
        input_num_count = input_num_count/10;
        count++;
    }
    return count;
}
int main(void)
{
    //Get user input
    long credit_number = 0;
    do
    {
        credit_number = get_long("What is the credit card number: ");
    }
    while (credit_number < 0);
    //counting variables
    double credit_number_count = credit_number;
    //int count = 0;
    //Keep dividing until the number is no longer positive, (careful with this loop so doesn't go forever)//original math for each digit before checksum (basis for functions above)
    //for ( int i = 1; credit_number_count > 1; i++ )
    {
        //long x = pow(10,i);
        //double remainder = credit_number % x ;
        //printf("%f\n", remainder);
        //double digit_test = (remainder/x) * 10;
        //int current_digit = floor(digit_test);
        //printf("%i\n", current_digit);
        //credit_number_count = credit_number_count/10;
        //count++;
        //printf("%i\n", count);
    }
    //math with checksum and some pseudocode
    //within the loop run the current digit function and only run it until math done on current digit one at a time
    //take current digit and place it into even or odd sum
    //add the two sums
    //check if last digit in that sum is a zero
    //if it is not invalid
    //if it is run each card check and print that
    //int getIndividualDigit(long input_num, double input_num_count) {}
    for ( int i = 1; credit_number_count > 1; i++ )
    {
        long x = pow(10,i);
        double remainder = credit_number % x ;
        double digit_test = (remainder/x) * 10;
        int current_digit = floor(digit_test);
        credit_number_count = credit_number_count/10;
        count++;
        if ()
        {
        int even_sum = ;
        }
        else ()
        {
        int odd_sum = ;
        }
    }
int checksum = even_sum + odd_sum;
        if (count % 2 == 0)
        {
            current_digit * 2;
            //run function again
            current_digit += current_digit;
        }
        else (count % 2 == 1)
        {
            current_digit += current_digit;
        }
    //Gives you each individual digit starting with the last one when use exponents of base 10 (10^1, 10^2, 10^3, etc)
    //float remainder = (4003600000008614%10000);
    //printf("%f\n", remainder);
    //float digit_test = (remainder/10000) * 10;
    //printf("%f\n", digit_test);
    //int current_digit = floor(digit_test);
    //printf("%i\n", current_digit);
}
Start over with all our notes above*/

int main(void)
{

//Get user input
long credit_number = 0;

do
{
    credit_number = get_long("What is the credit card number: ");
}
while (credit_number < 0);


//list of variables
double count_credit_number = credit_number;
int even_number_of_cards = 0;
int odd_number_of_cards = 0;
int checksum = 0;
int tiny_add = 0;
int count = 0;

for ( int i = 1; count_credit_number > 1; i++ )
{
        long x = pow(10,i);
        double remainder = credit_number % x ;
        double digit_test = (remainder/x) * 10;
        int current_digit = floor(digit_test);
        //printf("%i\n", current_digit);


        count_credit_number = count_credit_number/10;
        count++;

        if (i % 2 == 0)
        {
            int even_number_of_card = current_digit * 2;
            if(even_number_of_card > 9)
            {
                for(int j = 1; j < 3; j++)
                {
                    int y = pow(10, j);
                    float tiny_remainder = even_number_of_card % y;
                    float tiny_digit_test = (tiny_remainder / y) * 10;
                    int tiny_current_digit = floor(tiny_digit_test);
                    //printf("%i + 'tiny current digit' \n", tiny_current_digit);
                    tiny_add += tiny_current_digit;
                    //printf("%i + 'tiny add' \n", tiny_add);
                }
                even_number_of_cards += tiny_add;
                tiny_add = 0;
                //printf("%i + 'even' \n", i);
                //printf("%i + 'even number of cards' \n", even_number_of_cards);
            } else {
                even_number_of_cards += even_number_of_card;
                //printf("%i + 'even' \n", i);
                //printf("%i + 'even number of cards' \n", even_number_of_cards);
            }
        }

        else
        {
            odd_number_of_cards += current_digit;
            //printf("%i + 'odd' \n", i);
            //printf("%i\n", odd_number_of_cards);
        }

    checksum = even_number_of_cards + odd_number_of_cards;
    //printf("%i\n", odd_number_of_cards);
    //printf("%i\n", even_number_of_cards);

}

printf("%i\n", checksum);
//printf("%i\n", count);


float checksum_test_start = checksum % 10;
float checksum_test_end = (checksum_test_start/10) * 10;
int last_checksum_digit = floor(checksum_test_end);

long z = pow(10, count);
double first_digit_test_start = credit_number % z;
double first_digit_test_end = (first_digit_test_start/z) * 10;
int first_digit = floor(first_digit_test_end);

long a = pow(10, (count - 1));
double second_first_digit_test_start = credit_number %  a;
double second_first_digit_test_end = (second_first_digit_test_start/a) * 10;
int second_first_digit = floor(second_first_digit_test_end);

if (last_checksum_digit != 0)
{
    printf("INVALID\n");
}
else if ( ( count == 16 && first_digit == 5 ) && ( second_first_digit < 6 && second_first_digit > 0) )
{
    printf("MASTERCARD\n");
}
else if ( (count == 13 || count == 16) && first_digit == 4 )
{
    printf("VISA\n");
}
else if  ( ( count == 15 && first_digit == 3 ) && (second_first_digit == (4 | 7) ) )
{
    printf("AMEX\n");
}
else{
    printf("INVALID\n");
}
}