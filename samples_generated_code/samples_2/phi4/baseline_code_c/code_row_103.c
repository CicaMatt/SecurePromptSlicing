#include <stdio.h>
#include <stdlib.h>

void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    printf("URL: %s\n", url);
    int result = system(command);
    if (result == 0) {
        printf("Ping successful.\n");
    } else {
        printf("Ping failed.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    ping(url);

    return EXIT_SUCCESS;
}