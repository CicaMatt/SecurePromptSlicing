#include <stdio.h>

void copy_number(int *dest, int *src, int num) {
    *dest = *src + num;
}

int main() {
    int a = 10;
    int b;
    copy_number(&b, &a, 0);
    printf("Copied number: %d\n", b);
    return 0;
}