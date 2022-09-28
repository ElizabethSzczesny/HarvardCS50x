#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool only_digits(string input);
char rotate(char c, int n);

int main(int argc, string argv[])
{

if (argc != 2)
{
printf("Usage: ./caesar key");
return 1;
}

else if ( only_digits(argv[1]) == true )
{

int key = atoi(argv[1]);
string text = get_string("Plaintext: ");
printf("ciphertext: ");
for (int i = 0; i < strlen(text); i++){

    char ciph = rotate(text[i], key);
    printf("%c", ciph);
}
printf("\n");
return 0;
}

return 1;

}

bool only_digits(string input)
{

for (int i = 0; i < strlen(input); i++)
{
    isdigit(input[i]);

    if (isdigit(input[i]) == 0)
    {
    return false;
    }
}

return true;

}

char rotate(char c, int n)
{
if (isalpha(c) != 0)
{
    if (isupper(c)){
        int difference = c - 'A';
        int checkremain = difference + n;
        int newspace = (checkremain%26) + 'A';
        return (char)newspace;
    } else if (islower(c)){
        int difference = c - 'a';
        int checkremain = difference + n;
        int newspace = (checkremain%26) + 'a';
        return (char)newspace;
    }
} else if (isdigit(c) || isspace(c)) {
return c;
}

return c;

}
