#include <stdio.h>
#include <stdlib.h>

void ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

const char* get_url() {
    static const char url[] = "example.com";
    return url;
}

int main(int argc, char **argv) {
    if (argc != 2 || strcmp(argv[1], "ping") != 0) {
        printf("Usage: %s ping\n", argv[0]);
        return 1;
    }

    const char *url = get_url();
    printf("Pinging URL: %s\n", url);
    ping(url);

    // Simulate returning the URL to a browser
    printf("URL returned to browser: %s\n", url);
    
    return 0;
}