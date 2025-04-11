//Домашна работа: 
//3. Напишете програма, която разбива шифър на Виженер без да е известен ключа. Програмата да използва анализ на честотата. (проучете в Интернет как се модифицира анализа на честота, спрямо шифъра на Цезар)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_TEXT 10000
#define MAX_KEYLEN 20

double english_freq[26] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
    2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
    2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};

void clean_text(char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            output[j++] = toupper(input[i]);
        }
    }
    output[j] = '\0';
}

double index_of_coincidence(char *text, int len) {
    if (len < 2) return 0.0;
    int freq[26] = {0};
    for (int i = 0; i < len; i++) {
        freq[text[i] - 'A']++;
    }

    double ic = 0.0;
    for (int i = 0; i < 26; i++) {
        ic += freq[i] * (freq[i] - 1);
    }
    ic /= (double)(len * (len - 1));
    return ic;
}

int estimate_key_length(char *text, int len) {
    int best_len = 1;
    double best_ic = 0.0;

    for (int key_len = 1; key_len <= MAX_KEYLEN; key_len++) {
        double total_ic = 0.0;

        for (int i = 0; i < key_len; i++) {
            char group[MAX_TEXT];
            int k = 0;
            for (int j = i; j < len; j += key_len) {
                group[k++] = text[j];
            }
            total_ic += index_of_coincidence(group, k);
        }

        double avg_ic = total_ic / key_len;

        if (avg_ic > best_ic) {
            best_ic = avg_ic;
            best_len = key_len;
        }
    }

    return best_len;
}

int best_caesar_shift(char *group, int len) {
    double min_chi = 1e9;
    int best_shift = 0;

    for (int shift = 0; shift < 26; shift++) {
        int freq[26] = {0};
        for (int i = 0; i < len; i++) {
            int letter = (group[i] - 'A' - shift + 26) % 26;
            freq[letter]++;
        }

        double chi_sq = 0.0;
        for (int i = 0; i < 26; i++) {
            double observed = freq[i];
            double expected = english_freq[i] * len / 100.0;
            chi_sq += pow(observed - expected, 2) / (expected + 1e-6);
        }

        if (chi_sq < min_chi) {
            min_chi = chi_sq;
            best_shift = shift;
        }
    }

    return best_shift;
}

void recover_key(char *text, int len, int key_len, char *key_out) {
    for (int i = 0; i < key_len; i++) {
        char group[MAX_TEXT];
        int k = 0;
        for (int j = i; j < len; j += key_len) {
            group[k++] = text[j];
        }
        int shift = best_caesar_shift(group, k);
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
    char input[MAX_TEXT], clean[MAX_TEXT];
    char key[MAX_KEYLEN];
    char decrypted[MAX_TEXT];

    printf("Въведи шифриран текст:\n");
    fgets(input, MAX_TEXT, stdin);

    clean_text(input, clean);
    int len = strlen(clean);

    if (len < 10) {
        printf("Текстът е твърде кратък за анализ.\n");
        return 1;
    }

    int key_len = estimate_key_length(clean, len);
    printf("Предполагаема дължина на ключа: %d\n", key_len);

    recover_key(clean, len, key_len, key);
    printf("Открит ключ: %s\n", key);

    decrypt_vigenere(clean, len, key, key_len, decrypted);
    printf("Дешифриран текст:\n%s\n", decrypted);

    return 0;
}
