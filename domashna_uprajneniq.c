//Напишете програма, която въвежда текст и генерира Цезаров шифър на текста. Програмата трябва да поддържа малки и големи латински букви, цифри и разстояние. 
//Добавете поддръжка на специални символи. Добавете употреба на файлове.

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
    char text[MAXN];
    char filename[] = "input.txt";  
    char output_filename[] = "output.txt"; 
    int key;

    read_from_file(filename, text);
    printf("Прочетен текст от файла: %s\n", text);

    printf("Въведете ключ за шифроване (цяло число): ");
    scanf("%d", &key);

    char* cipher = cezar_cipher(text, key);
    printf("Шифрован текст: %s\n", cipher);
  
    write_to_file(output_filename, cipher);
    printf("Шифрованието е записано във файл '%s'.\n", output_filename);

    free(cipher);

    return 0;
}
