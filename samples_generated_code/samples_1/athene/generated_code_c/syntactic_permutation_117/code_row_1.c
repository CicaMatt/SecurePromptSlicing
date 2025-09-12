#include <stdio.h>
#include <stdlib.h>

char* itoa(int value, char *result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* out = result;
    int quotient = value;

    // We need to handle negative numbers for base 10
    if (value < 0 && base == 10) {
        *out++ = '-';
        quotient = -value;
    }

    int n = 0;
    while (quotient > 0) {
        int remainder = quotient % base;
        *out++ = "0123456789abcdefghijklmnopqrstuvwxyz"[remainder];
        ++n;
        quotient /= base;
    }
    
    if (n == 0) { *out++ = '0'; }

    // Reverse the string
    for (int i = 0; i < n / 2; ++i) {
        char temp = result[i];
        result[i] = out[-(i + 1)];
        out[-(i + 1)] = temp;
    }
    *out = '\0';

    return result;
}

int main() {
    int a = 123, b = -456, c = 789;
    char str_a[32], str_b[32], str_c[32];

    itoa(a, str_a, 10);
    itoa(b, str_b, 10);
    itoa(c, str_c, 10);

    printf("%s\n%s\n%s\n", str_a, str_b, str_c);
    return 0;
}