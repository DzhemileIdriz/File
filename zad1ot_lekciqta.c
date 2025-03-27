#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000
#define ALPHA_LENGTH 26

//Да се напише програма реализираща шифър на Цезар с постоянно отместване. На входа се задава чистия текст, на изхода излиза криптираното съобщение и с брутфорс разкриптиране на криптирания текст.

char* cezar_cipher(char* str, int key) {
    int length = strlen(str);
    char* cipher = (char*) malloc(sizeof(char) * (length + 1));
  
    key = (key % ALPHA_LENGTH + ALPHA_LENGTH) % ALPHA_LENGTH;

    for (int i = 0; i < length; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            cipher[i] = ((str[i] - 'a' + key) % ALPHA_LENGTH) + 'a';
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            cipher[i] = ((str[i] - 'A' + key) % ALPHA_LENGTH) + 'A';
        } else {
            cipher[i] = str[i];  
        }
    }
    
    cipher[length] = '\0';
    return cipher;
}

void cezar_bruteforce(char* cipher) {
    for (int key = 0; key < ALPHA_LENGTH; key++) {
        int length = strlen(cipher);
        char plaintext[MAXN];

        for (int i = 0; i < length; i++) {
            if (cipher[i] >= 'a' && cipher[i] <= 'z') {
                plaintext[i] = ((cipher[i] - 'a' - key + ALPHA_LENGTH) % ALPHA_LENGTH) + 'a';
            } else if (cipher[i] >= 'A' && cipher[i] <= 'Z') {
                plaintext[i] = ((cipher[i] - 'A' - key + ALPHA_LENGTH) % ALPHA_LENGTH) + 'A';
            } else {
                plaintext[i] = cipher[i];  
            }
        }

        plaintext[length] = '\0';
        printf("Ключ %2d: %s\n", key, plaintext);
    }
}

int main() {
    char str[MAXN];
    int key;

    printf("Въведете текст за шифроване: ");
    fgets(str, MAXN, stdin);

    size_t len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    printf("Въведете ключ за шифроване: ");
    scanf("%d", &key);

    char* cipher = cezar_cipher(str, key);
    printf("Шифрован текст: %s\n", cipher);

    printf("\n--- Брутфорс разшифроване ---\n");
    cezar_bruteforce(cipher);

    free(cipher);  
    return EXIT_SUCCESS;
}
