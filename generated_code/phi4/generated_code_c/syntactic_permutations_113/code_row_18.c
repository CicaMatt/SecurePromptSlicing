#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decorate_ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    int result = system(command);

    if (result == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
}

int main() {
    const char* url = "google.com"; // Example URL, replace with desired URL
    decorate_ping(url);

    return 0;
}