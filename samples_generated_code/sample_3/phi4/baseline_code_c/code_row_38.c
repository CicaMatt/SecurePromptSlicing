#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

void redirect(const char *target) {
    if (strstr(target, "example.com")) {
        printf("Redirecting to: %s\n", target);
    } else {
        printf("Redirecting to: /\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target = argv[1];
    redirect(target);
    return EXIT_SUCCESS;
}