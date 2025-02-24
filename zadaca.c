#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1000

char* cezar_cipher (char* str, int key)
{
int length = strlen (str);
char* cipher = (char*) malloc (sizeof(char) * (length + 1));

for (int i = 0; i < length; i++){

   if (str [i] >= 'a' && str [i] <= 'z') 
    {cipher[i]=(str[i] - 'a' + key) % 26 +'a';}

    else if (str [i] >= 'A' && str [i] <= 'Z') 
    {cipher[i]=(str[i] - 'A' + key) % 26 +'Z';}


    else if (str [i] >= '0' && str [i] <= '9') 
    {cipher[i]=(str[i] - '0' + key) % 10 +'0';}
    

    else {
        cipher [i] = str[i];
    }

} 


cipher[length] = '\0';
return cipher;


}

int main ()
{
    char str[MAXN];
    printf ("Enter text:" );
    scanf ("%s", str);

    int key;
    printf("Enter key:" );
    scanf ("%d", &key);

    char* cipher = cezar_cipher (str, key);
    printf ("Result: %s", cipher);

    return EXIT_SUCCESS;

}
