#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TARGET_LENGTH 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return 1;
    }

    char target[MAX_TARGET_LENGTH];
    strncpy(target, argv[1], sizeof(target));
    target[sizeof(target) - 1] = '\0';

    // Regular expression matching "."
    if (strcmp(target, ".") == 0) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to: /\n");
    }

    return 0;
}