//Домашна работа: 1. Добавете възможност на програмата да чете съобщение от файл, да се въвежда само ключ и да генерира файл с криптираното съобщение.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXN 1000

char* vigenereEncrypt(char* plaintext, char* key)
{
    int length = strlen(plaintext);
    int keyLength = strlen(key);
    char* cipher = (char*) malloc(sizeof(char) * (length + 1));
    memset(cipher, '\0', sizeof(char) * (length + 1));

    for(int i = 0; i < length; i++)
    {
        if(isalpha(plaintext[i]))
        {
            int shift = tolower(key[i % keyLength]) - 'a';

            if(islower(plaintext[i]))
                cipher[i] = 'a' + (plaintext[i] - 'a' + shift) % 26;
            else
                cipher[i] = 'A' + (plaintext[i] - 'A' + shift) % 26;
        }
        else
        {
            cipher[i] = plaintext[i];    
        }
    }

    cipher[length] = '\0';
    return cipher;
}

void write_to_file(const char *filename, const char *text) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "%s", text);
        fclose(file);
    } else {
        printf("Грешка при отваряне на файла за запис.\n");
    }
}

void read_from_file(const char *filename, char *text) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fgets(text, MAXN, file);  
        fclose(file);
    } else {
        printf("Грешка при отваряне на файла за четене.\n");
    }
}

int main() {
    char plaintext[MAXN];
    char key[MAXN];
    char filename[MAXN];         
    char output_filename[MAXN];   

    printf("Въведи име на входен файл: ");
    scanf("%s", filename);

    read_from_file(filename, plaintext);

    printf("Въведи ключ за криптиране: ");
    scanf("%s", key);

    char* encrypted = vigenereEncrypt(plaintext, key);

    printf("Въведи име на изходен файл: ");
    scanf("%s", output_filename);

    write_to_file(output_filename, encrypted);

    printf("Криптираният текст е записан във файл: %s\n", output_filename);

    free(encrypted);
    return 0;
}

