#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{

string reading = get_string("Text: ");

float lettersnum = count_letters(reading);
float wordsnum = count_words(reading);
float sentencenum = count_sentences(reading);

int index = 0;

float L = lettersnum / wordsnum * (float)100;
float S = sentencenum / wordsnum * (float)100;

index = round(0.0588 * L - 0.296 * S - 15.8);

//printf ("%f\n", L);
//printf ("%f\n", S);

if (index < 1) {

printf ("Before Grade 1\n");

} else if (index >= 16) {

printf ("Grade 16+\n");

} else {

printf ("Grade %i\n", index);

}

}

int count_letters(string text)
{

int len = strlen(text);
int num = 0;

    for (int i = 0; i < len; i++){
        if (isupper(text[i]) || islower(text[i])){
            num ++;
        }
    }

//printf("%i letters\n", num);
return num;

}

int count_words(string text)
{

int len = strlen(text);
int num2 = 1;

    for (int i = 0; i < len; i++){
        if (isspace(text[i])){
            num2 ++;
        }
    }

//printf("%i words\n", num2);
return num2;

}

int count_sentences(string text)
{

int len = strlen(text);
int num3 = 0;

    for (int i = 0; i < len; i++){
        if (text[i] == '.' || text[i] == '!' || text[i] == '?'){
            num3 ++;
        }
    }

//printf("%i sentences\n", num3);
return num3;

}