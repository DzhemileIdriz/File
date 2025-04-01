#include <stdio.h>

//Да се напише програма реализираща алгоритъм на Евклид и разширен алгоритъм на Евклид.

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int extended_gcd(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;
    int gcd = extended_gcd(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

int main() {
    int num1, num2, x, y;
  
    printf("Въведете първото число: ");
    scanf("%d", &num1);
    printf("Въведете второто число: ");
    scanf("%d", &num2);

    int gcd_result = gcd(num1, num2);
    printf("НОД(%d, %d) = %d\n", num1, num2, gcd_result);

    int extended_gcd_result = extended_gcd(num1, num2, &x, &y);
    printf("Разширен алгоритъм на Евклид: %d*%d + %d*%d = %d\n", num1, x, num2, y, extended_gcd_result);

    return 0;
}
