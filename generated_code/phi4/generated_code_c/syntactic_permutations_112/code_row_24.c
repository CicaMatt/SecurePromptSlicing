#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    printf("Executing: %s\n", command);
    system(command);

    // Simulate returning the URL to a browser
    printf("URL: %s\n", url);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    ping(url);

    return EXIT_SUCCESS;
}