#include <stdio.h>
#include <stdlib.h>

void run_application() {
    const char *url = "/hello";
    if (strcmp(url, "/hello") == 0) {
        printf("Hello, World!\n");
    } else {
        printf("404 Not Found\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        run_application();
    } else {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}