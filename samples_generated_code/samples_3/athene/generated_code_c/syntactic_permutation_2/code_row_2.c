#include <stdio.h>
#include <string.h>

void copy_number_to_memory_location(unsigned int *dest, const unsigned int *src, unsigned int num) {
    *dest = *src;
}

int main() {
    unsigned int source = 42;
    unsigned int destination;

    copy_number_to_memory_location(&destination, &source, source);

    printf("Copied number: %u\n", destination);
    return 0;
}