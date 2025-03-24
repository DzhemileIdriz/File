#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXN 1000

int read_cipher(char* filename, char* cipher){

    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("Error opening file");
        return EXIT_FAILURE;
    } 

    if(fgets (cipher, MAXN, fp) == NULL) {
        printf("Error reading from file");
        return EXIT_FAILURE;
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

void write_text(char* filename, char* text) {
    FILE *fp = fopen(filename, "myfile");
    fprintf(fp, "%s", text);
    fclose(fp);
}

char* vigenere_encrypt(char* plaintext, char* key) 
{
    int text_length = strlen(plaintext);
    int key_length = strlen(key);

    char* cipher = (char*) malloc(sizeof(char) * (text_length + 1));
    memset(cipher, '\0', sizeof(char) * (text_length + 1));
    for(int i = 0; i < text_length; i++)
    {
        if(isalpha(plaintext[i]))
        {
            int shift = tolower(key[i % key_length]) - 'a';
            if(islower(plaintext[i]))
            {
                cipher[i] = 'a' + (plaintext[i] - 'a' + shift) % 26;
            }
            else if(isupper(plaintext[i]))
            {
                cipher[i] = 'A' + (plaintext[i] - 'A' + shift) % 26;
            } 
        }
        else if(isdigit(plaintext[i]))
        {
            int shift = tolower(key[i % key_length]) - 'a';
            cipher[i] = '0' + (plaintext[i] - '0' + shift) % 10;
        }
        else
        {
            cipher[i] = plaintext[i];
        }
    }

    cipher[text_length] = '\0';
    return cipher;
}

char* vigenere_decrypt(char* cipher, char* key)
{
    int text_length = strlen(cipher);
    int key_length = strlen(key);

    char* decipher = (char*) malloc(sizeof(char) * (text_length + 1));
    memset(decipher, '\0', sizeof(char) * (text_length + 1));
    for(int i = 0; i < text_length; i++)
    {
        if(isalpha(cipher[i]))
        {
            int shift = tolower(key[i % key_length]) - 'a';
            if(islower(cipher[i]))
            {
                decipher[i] = (cipher[i] - 'a' - shift + 26) % 26 + 'a';
            }
            else if(isupper(cipher[i]))
            {
                decipher[i] = (cipher[i] - 'A' - shift + 26) % 26 + 'A';
            } 
        } 
        else if(isdigit(cipher[i]))
        {
            {
                int shift = tolower(key[i % key_length]) - 'a';
                decipher[i] = (cipher[i] - '0' - shift + 10) % 10 + '0';
            }
        }
        else
        {
            decipher[i] = cipher[i];
        }
    }

    decipher[text_length] = '\0';
    return decipher;
}


int main()
{
    printf("Enter filename for text.\n");
    char filename[MAXN];
    scanf("%s", filename);
    char text[MAXN];
    read_cipher(filename, text);
    printf("Enter filename for key.\n");
    scanf("%s", filename);
    char key[MAXN];
    read_cipher(filename, key);
    char* cipher = vigenere_encrypt(text, key);
    printf("The encryped message is :%s\n", cipher);
    write_text("vigenere_result.txt", cipher);
    char* decrypted_cipher = vigenere_decrypt(cipher, key);
    printf("Enter filename for decrypted cipher.\n");
    scanf("%s", filename);
    write_text(filename, decrypted_cipher);
    free(cipher);
    free(decrypted_cipher);
    return EXIT_SUCCESS;
}
