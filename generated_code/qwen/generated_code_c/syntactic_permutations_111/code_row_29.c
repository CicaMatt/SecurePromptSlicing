#include <stdio.h>
#include <stdlib.h>

void ping(const char* path) {
    char url[256];
    snprintf(url, sizeof(url), "http://%s", path);
    
    char command[512];
    snprintf(command, sizeof(command), "ping -c 4 %s", url + 7); // Assuming URL is http://example.com

    system(command);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    ping(argv[1]);

    return 0;
}