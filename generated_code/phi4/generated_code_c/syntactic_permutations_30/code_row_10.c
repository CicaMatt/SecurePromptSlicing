#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TARGET_MAX_LEN 256

int matches_regex(const char *target) {
    if (strlen(target) == 0) return 0;
    for (size_t i = 0; i < strlen(target); ++i) {
        if (!((target[i] >= 'a' && target[i] <= 'z') ||
              (target[i] >= 'A' && target[i] <= 'Z') ||
              (target[i] >= '0' && target[i] <= '9'))) {
            return 0;
        }
    }
    return 1;
}

void redirect_user(const char *target) {
    if (matches_regex(target)) {
        printf("Redirecting to: /%s\n", target);
    } else {
        printf("Redirecting to: /\n");
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    redirect_user(target);

    return EXIT_SUCCESS;
}