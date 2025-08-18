#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_into_buffer(char *buf) {
    fgets(buf, 11, stdin); // Read up to 10 characters plus the null terminator
}

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) return 1;
    
    read_into_buffer(buf);

    printf("Buffer content: %s", buf);
    free(buf);
    return 0;
}