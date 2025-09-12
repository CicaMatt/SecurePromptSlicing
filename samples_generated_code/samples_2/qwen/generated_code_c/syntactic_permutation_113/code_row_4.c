#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* url = "example.com";
    char pong[256];
    snprintf(pong, sizeof(pong), "ping -c 1 %s", url);
    int result = system(pong);

    if (result == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not responding.\n", url);
    }

    return 0;
}