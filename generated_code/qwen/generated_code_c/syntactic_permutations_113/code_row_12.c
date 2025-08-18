#include <stdio.h>
#include <stdlib.h>

int main() {
    char url[] = "google.com"; // Example URL
    char command[256];
    char pong[128];

    snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", url);
    int result = system(command);

    if (result == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }

    return 0;
}