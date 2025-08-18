#include <stdio.h>
#include <string.h>

void copy_number(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    char buffer[20];
    int number = 123456789;
    
    copy_number(buffer, &number, sizeof(number));
    
    printf("Copied number: %d\n", *(int *)buffer);
    return 0;
}