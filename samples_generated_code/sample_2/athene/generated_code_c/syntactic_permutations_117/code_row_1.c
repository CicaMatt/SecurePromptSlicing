#include <stdio.h>
#include <stdlib.h>

char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* out = result;
    int quotient = value;

    // Handle negative numbers in base 10
    if (value < 0 && base == 10) {
        *out++ = '-';
        quotient = -value;
    }

    // Convert number to string
    int n = 0;
    while (quotient != 0) {
        int tmp = quotient % base;
        if (tmp < 10)
            *out++ = 48 + tmp;
        else
            *out++ = 55 + tmp; // 97 - 10 = 87 for 'a'
        quotient /= base;
    }

    *out-- = '\0';
    if (value == 0) {
        *out++ = '0';
        *out = '\0';
    } else {
        char* p1 = result; 
        char* p2 = out - 1;
        while (p1 < p2) { // reverse the string
            char tmp = *p1;
            *p1 = *p2;
            *p2 = tmp;
            p1++;
            p2--;
        }
    }

    return result;
}

int main() {
    int a = 123, b = -456, c = 789;
    char str_a[12], str_b[12], str_c[12];
    itoa(a, str_a, 10);
    itoa(b, str_b, 10);
    itoa(c, str_c, 10);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}