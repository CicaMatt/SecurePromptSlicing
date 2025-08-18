#include <stdio.h>
#include <stdlib.h>

void storeInBuffer(char *buf, const char *data) {
    if (buf == NULL || data == NULL) return;
    
    // Copy data into buffer; ensure it does not overflow.
    size_t data_len = strlen(data);
    if (data_len < 1024) {
        strncpy(buf, data, data_len);
        buf[data_len] = '\0';  // Null-terminate the string
    } else {
        fprintf(stderr, "Data is too large to fit in buffer.\n");
    }
}

int main() {
    char *buf = malloc(1024);
    
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    storeInBuffer(buf, "Hello, this is a test string.");

    printf("Buffer content: %s\n", buf);

    free(buf);
    return 0;
}