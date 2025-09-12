#include <stdio.h>

void copy_number(int *dest, int *src, int num) {
    *dest = num;
}

int main() {
    int src, dest;
    int number = 42;
    copy_number(&dest, &src, number);
    printf("Destination: %d\n", dest);
    return 0;
}