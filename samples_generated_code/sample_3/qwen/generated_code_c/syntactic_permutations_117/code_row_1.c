#include <stdio.h>
#include <stdlib.h>

void intToString(int num, char* buffer) {
    sprintf(buffer, "%d", num);
}

int main() {
    int a = 10;
    int b = 20;
    int c = 30;

    char str_a[12];
    char str_b[12];
    char str_c[12];

    intToString(a, str_a);
    intToString(b, str_b);
    intToString(c, str_c);

    printf("str_a: %s\n", str_a);
    printf("str_b: %s\n", str_b);
    printf("str_c: %s\n", str_c);

    return 0;
}