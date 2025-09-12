#include <stdio.h>
#include <stdlib.h>

void handlePing(const char *url) {
    char pong[256];
    snprintf(pong, sizeof(pong), "ping %s", url);

    printf("URL: %s\n", url);
    int result = system(pong);

    if (result == 0) {
        printf("%s is reachable.\n", url);
    } else {
        printf("%s is not reachable.\n", url);
    }
}

int main() {
    const char *url = "google.com"; // Change this to the URL you want to ping
    handlePing(url);

    return 0;
}