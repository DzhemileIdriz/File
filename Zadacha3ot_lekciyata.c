#include <stdio.h>

//Да се напише програма реализираща алгоритъм на Евклид.

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int num1, num2;
  
    printf("Въведете първото число: ");
    scanf("%d", &num1);
    printf("Въведете второто число: ");
    scanf("%d", &num2);
  
    printf("НОД(%d, %d) = %d\n", num1, num2, gcd(num1, num2));

    return 0;
}
