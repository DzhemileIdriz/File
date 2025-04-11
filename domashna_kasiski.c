//Домашна работа: 4. Напишете програма, която разбива шифъра на Виженер по метода на Касиски.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_TEXT 10000
#define MAX_KEYLEN 20

double index_of_coincidence(char *text, int len) {
    int freq[26] = {0};
    for (int i = 0; i < len; i++) {
        if (isupper(text[i]))
            freq[text[i] - 'A']++;
    }

    double ic = 0.0;
    for (int i = 0; i < 26; i++) {
        ic += freq[i] * (freq[i] - 1);
    }
    ic /= (double)(len * (len - 1));
    return ic;
}

double english_freq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
    2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};

int estimate_key_length(char *text, int text_len) {
    double avg_ics[MAX_KEYLEN] = {0};

    for (int key_len = 1; key_len <= MAX_KEYLEN; key_len++) {
        double sum_ic = 0.0;

        for (int i = 0; i < key_len; i++) {
            char group[MAX_TEXT];
            int k = 0;
            for (int j = i; j < text_len; j += key_len) {
                group[k++] = text[j];
            }
            sum_ic += index_of_coincidence(group, k);
        }

        avg_ics[key_len] = sum_ic / key_len;
    }

    int best_len = 1;
    double best_ic = 0;
    for (int i = 1; i <= MAX_KEYLEN; i++) {
        if (avg_ics[i] > best_ic) {
            best_ic = avg_ics[i];
            best_len = i;
        }
    }

    return best_len;
}

void recover_key(char *text, int text_len, int key_len, char *key_out) {
    for (int i = 0; i < key_len; i++) {
        int freq[26] = {0};
        int k = 0;
        for (int j = i; j < text_len; j += key_len) {
            freq[text[j] - 'A']++;
            k++;
        }

        int max_f = 0, max_idx = 0;
        for (int f = 0; f < 26; f++) {
            if (freq[f] > max_f) {
                max_f = freq[f];
                max_idx = f;
            }
        }

       
        int shift = (26 + max_idx - ('E' - 'A')) % 26;
        key_out[i] = 'A' + shift;
    }

    key_out[key_len] = '\0';
}

void decrypt_vigenere(char *text, int len, char *key, int key_len, char *output) {
    for (int i = 0; i < len; i++) {
        int k = key[i % key_len] - 'A';
        output[i] = ((text[i] - 'A' - k + 26) % 26) + 'A';
    }
    output[len] = '\0';
}

int main() {
    char ciphertext[MAX_TEXT];
    printf("Въведи шифриран текст (само главни букви, без интервали):\n");
    scanf("%s", ciphertext);

    int text_len = strlen(ciphertext);

    int key_len = estimate_key_length(ciphertext, text_len);
    printf("Открита дължина на ключа: %d\n", key_len);

    char key[MAX_KEYLEN];
    recover_key(ciphertext, text_len, key_len, key);
    printf("Открит ключ: %s\n", key);

    char plaintext[MAX_TEXT];
    decrypt_vigenere(ciphertext, text_len, key, key_len, plaintext);
    printf("Дешифриран текст:\n%s\n", plaintext);

    return 0;
}
