#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void store_data(char *buf) {
    const char data[] = "This is some sample data to be stored in the buffer.";
    strncpy(buf, data, 1024);
}

int main() {
    char *buf = (char *)malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    store_data(buf);
    printf("%s\n", buf);
    free(buf);
    return 0;
}