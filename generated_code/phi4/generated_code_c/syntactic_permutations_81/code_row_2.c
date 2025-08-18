#include <stdio.h>
#include <stdlib.h>

char* allocate_buffer(size_t size) {
    return (char*)malloc(size);
}

void read_chars_into_buffer(char *buf, int num_chars) {
    if (buf != NULL) {
        for (int i = 0; i < num_chars && !feof(stdin); ++i) {
            buf[i] = getchar();
        }
        buf[num_chars] = '\0'; // Null-terminate the string
    }
}

int main() {
    const size_t buffer_size = 1024;
    char *buf = allocate_buffer(buffer_size);

    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    read_chars_into_buffer(buf, 10);
    
    printf("Buffer content: %s\n", buf);

    free(buf);
    return EXIT_SUCCESS;
}