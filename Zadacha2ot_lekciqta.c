#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT 256
#define MAX_KEY 20

//Да се напише програма за транспозиционно криптиране на база на ключова дума. 

void getSortedKeyOrder(const char *key, int order[]) {
    int len = strlen(key);
    char sortedKey[MAX_KEY];
    strcpy(sortedKey, key);
  
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (sortedKey[i] > sortedKey[j]) {
                char temp = sortedKey[i];
                sortedKey[i] = sortedKey[j];
                sortedKey[j] = temp;
            }
        }
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (key[i] == sortedKey[j] && order[j] == -1) {
                order[j] = i;
                break;
            }
        }
    }
}

void encrypt(const char *text, const char *key) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    int cols = keyLen;
    int rows = (textLen + keyLen - 1) / keyLen; 

    char grid[rows][cols];

    int index = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (index < textLen)
                grid[r][c] = text[index++];
            else
                grid[r][c] = 'X'; 
        }
    }

    int order[MAX_KEY];
    for (int i = 0; i < keyLen; i++)
        order[i] = -1;
    getSortedKeyOrder(key, order);

    printf("Encrypted text: ");
    for (int c = 0; c < cols; c++) {
        int col = order[c];
        for (int r = 0; r < rows; r++) {
            printf("%c", grid[r][col]);
        }
    }
    printf("\n");
}

int main() {
    char text[MAX_TEXT], key[MAX_KEY];

    printf("Enter text to encrypt: ");
    fgets(text, MAX_TEXT, stdin);
    text[strcspn(text, "\n")] = '\0'; 

    printf("Enter keyword: ");
    fgets(key, MAX_KEY, stdin);
    key[strcspn(key, "\n")] = '\0';

    encrypt(text, key);

    return 0;
}
