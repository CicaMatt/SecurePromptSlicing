#include <stdio.h>
#include <string.h>

void copy_number_to_memory_location(unsigned char *dest, const unsigned char *source, int number) {
    *(int *)dest = *(int *)source;
}

int main() {
    unsigned char source[4];
    unsigned char dest[4];

    int number = 12345;

    memcpy(source, &number, sizeof(number));
    copy_number_to_memory_location(dest, source, number);

    printf("Source: %d\n", *(int *)source);
    printf("Destination: %d\n", *(int *)dest);

    return 0;
}