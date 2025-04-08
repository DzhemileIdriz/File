//Домашна работа: Напишете програма, която въвежда текст и генерира Цезаров шифър на текста. Програмата трябва да поддържа малки и големи латински букви, цифри и разстояние.
//Напишете и програма, която въвежда шифър и ключ и декодира въведения шифър. Бонус: добавете поддръжка на специални символи. Бонус 2: Добавете употреба на файлове.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000
#define ALPHA_LENGTH 26

char* cezar_cipher(char* str, int key) {
    int length = strlen(str);
    char* cipher = (char*) malloc(sizeof(char) * (length + 1)); 

    key = (key % ALPHA_LENGTH + ALPHA_LENGTH) % ALPHA_LENGTH; 

    for (int i = 0; i < length; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            cipher[i] = ((str[i] - 'a' + key) % ALPHA_LENGTH) + 'a'; 
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            cipher[i] = ((str[i] - 'A' + key) % ALPHA_LENGTH) + 'A'; 
        } else if (str[i] >= '0' && str[i] <= '9') {
            cipher[i] = (str[i] - '0' + key) % 10 + '0'; 
        } else {
            cipher[i] = str[i]; 
        }
    }

    cipher[length] = '\0'; 
    return cipher;
}

char* cezar_decipher(char* cipher, int key) {
    int length = strlen(cipher);
    char* plaintext = (char*) malloc(sizeof(char) * (length + 1));

    key = (key % ALPHA_LENGTH + ALPHA_LENGTH) % ALPHA_LENGTH; 

    for (int i = 0; i < length; i++) {
        if (cipher[i] >= 'a' && cipher[i] <= 'z') {
            plaintext[i] = (cipher[i] - 'a' - key + ALPHA_LENGTH) % ALPHA_LENGTH + 'a'; 
        } else if (cipher[i] >= 'A' && cipher[i] <= 'Z') {
            plaintext[i] = (cipher[i] - 'A' - key + ALPHA_LENGTH) % ALPHA_LENGTH + 'A'; 
        } else if (cipher[i] >= '0' && cipher[i] <= '9') {
            plaintext[i] = (cipher[i] - '0' - key + 10) % 10 + '0'; 
        } else {
            plaintext[i] = cipher[i]; 
        }
    }

    plaintext[length] = '\0'; 
    return plaintext;
}

void write_to_file(const char *filename, const char *text) {
    FILE *file = fopen(filename, "wb");
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
    char text[MAXN];
    char filename[] = "encrypted.txt"; 
    int key;

    printf("Въведете текст за шифроване: ");
    fgets(text, MAXN, stdin);

    printf("Въведете ключ за шифроване (цяло число): ");
    scanf("%d", &key);

    char* cipher = cezar_cipher(text, key);
    printf("Шифрован текст: %s\n", cipher);

    write_to_file(filename, cipher);
    printf("Шифрованието е записано във файл '%s'.\n", filename);

    char cipher_from_file[MAXN];
    read_from_file(filename, cipher_from_file);
    printf("Прочетен текст от файл: %s\n", cipher_from_file);

    printf("Въведете ключ за декодиране (цяло число): ");
    scanf("%d", &key);

    char* plaintext = cezar_decipher(cipher_from_file, key);
    printf("Декодиран текст: %s\n", plaintext);

    free(cipher);
    free(plaintext);

    return 0;
}
