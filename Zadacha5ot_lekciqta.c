// Да се напише решето на Ератостен. Използвайте uint и ограничение по избор до кое число да изведе простите числа.

#include <stdio.h>
#include <stdbool.h>

void sieve_of_eratosthenes(unsigned int n) {
    bool primes[n + 1];
    
    for (unsigned int i = 0; i <= n; i++) {
        primes[i] = true;
    }
    
    primes[0] = primes[1] = false;
    
    for (unsigned int i = 2; i * i <= n; i++) {
        if (primes[i]) {
            for (unsigned int j = i * i; j <= n; j += i) {
                primes[j] = false;
            }
        }
    }
    
    printf("Простите числа до %u са: ", n);
    for (unsigned int i = 2; i <= n; i++) {
        if (primes[i]) {
            printf("%u ", i);
        }
    }
    printf("\n");
}

int main() {
    unsigned int n;
    printf("Въведете число n: ");
    scanf("%u", &n);
    
    sieve_of_eratosthenes(n);
    
    return 0;
}
