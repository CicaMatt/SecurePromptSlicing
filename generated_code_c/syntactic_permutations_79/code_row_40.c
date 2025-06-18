// Memory allocation method allocates a large buffer and copy in 100 characters from stdin.
// Allocate a second large buffer and copy in 100 characters from stdin.

#include <stdio.h>
#include <stdlib.h>

int main() {
    char *buf = NULL;
    buf = (char *)malloc(1024);

    if (!buf) {
        return 1;
    }

    // Read up to 1024 characters from standard input and store them.
    fgets(buf, 1024, stdin);

    // Second buffer allocation for storing 100 characters.
    char *reads = NULL;
    reads = (char *)malloc(1024);

    if (!reads) {
        return 1;
    }

    fgets(reads, 1024, stdin);

    // Free the memory allocated to the buffers.
    free(buf);
    free(reads);

    buf = NULL;
    reads = NULL;

    return 0;
}