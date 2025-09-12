#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void handle_request(const char *url);
int ping(const char *url);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    handle_request(url);
    
    return EXIT_SUCCESS;
}

void handle_request(const char *url) {
    printf("Handling request for URL: %s\n", url);

    if (ping(url)) {
        printf("Ping successful!\n");
    } else {
        fprintf(stderr, "Ping failed.\n");
    }

    // Send the URL back to the browser (simulated by printing)
    printf("URL returned to client: %s\n", url);
}

int ping(const char *url) {
    char command[256];
    
    snprintf(command, sizeof(command), "ping -c 1 %s", url);

    int result = system(command);
    return WEXITSTATUS(result) == 0;
}