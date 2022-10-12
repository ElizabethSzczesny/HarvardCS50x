#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool twenty_six(string input);
char substitute(char ch, string key);

int main(int argc, string argv[])
{

if (argc != 2)
{
printf("Usage: ./substitution key\n");
return 1;
}
else if ( twenty_six(argv[1]) == true )
{

string key = argv[1];
string text = get_string("plaintext: ");
printf("ciphertext: ");
for (int i = 0; i < strlen(text); i++){

    char ciph = substitute(text[i], key);
    printf("%c", ciph);
}
printf("\n");
return 0;
}

return 1;

}

bool twenty_six(string input)
{
int l = strlen(input);
if (l != 26){
printf("Key must contain 26 characters\n");
return false;
}
for (int i = 0; i < strlen(input); i++)
{
    int count = 0;
    if(isalpha(input[i]) != 0)
    {
    char x = input[i];
    for (int j = 0; j < strlen(input); j++){
        if (x == input[j]){
            count++;
        }
    }
    } else {
    printf("Key must contain only alphabetical characters\n");
    return false;
    }

if (count != 1){
    printf("Key must contain each letter only once\n");
    return false;
}
}
return true;
}

//key maps to numbers 1-26

//and input letters always map to their corresponsing number

char substitute(char ch, string key)
{
char abclower[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char abcupper[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

if islower(ch){
    for (int j = 0; j < strlen(abclower); j++){
            if (ch == abclower[j])
            {
                ch = key[j];
                return tolower(ch);
            }
    }
}
else if (isupper(ch))
{
    for (int j = 0; j < strlen(abcupper); j++){
            if (ch == abcupper[j])
            {
                ch = key[j];
                return toupper(ch);
            }
    }
}
return ch;
}




