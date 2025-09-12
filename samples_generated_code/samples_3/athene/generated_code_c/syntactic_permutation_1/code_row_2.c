#include <stdio.h>

void copy_number(int *dest, int *source, int num) {
    *dest = *source;
}

int main() {
    int src = 42;
    int dest;

    copy_number(&dest, &src, 0);

    printf("Destination: %d\n", dest);
    return 0;
}