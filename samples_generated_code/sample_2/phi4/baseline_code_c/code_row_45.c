#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {
    char buffer[BUFFER_SIZE];

    // Overwrite all values in the buffer with 'A'
    memset(buffer, 'A', sizeof(buffer));

    // Print buffer for verification (optional)
    printf("Buffer content:\n%s\n", buffer);

    return 0;
}