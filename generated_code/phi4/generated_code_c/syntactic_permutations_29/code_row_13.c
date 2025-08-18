#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    const char *pattern = "example\\.com";
    
    // Check if the target matches the pattern
    if (strstr(target, pattern)) {
        printf("Location: http://%s\n", target);
    } else {
        printf("Location: /\n");
    }

    return EXIT_SUCCESS;
}