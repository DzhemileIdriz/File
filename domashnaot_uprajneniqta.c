//Напишете и програма, която въвежда шифър и ключ и декодира въведения шифър. Добавете поддръжка на специални символи. Добавете употреба на файлове.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000
#define ALPHA_LENGTH 26

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
    char cipher[MAXN];
    char filename[] = "input_encrypted.txt";  
    char output_filename[] = "output_decrypted.txt"; 
    int key;

    read_from_file(filename, cipher);
    printf("Прочетен шифрован текст от файла: %s\n", cipher);

    printf("Въведете ключ за декодиране (цяло число): ");
    scanf("%d", &key);

    char* plaintext = cezar_decipher(cipher, key);
    printf("Декодиран текст: %s\n", plaintext);

    write_to_file(output_filename, plaintext);
    printf("Декодиран текст е записан във файл '%s'.\n", output_filename);

    free(plaintext);

    return 0;
}
