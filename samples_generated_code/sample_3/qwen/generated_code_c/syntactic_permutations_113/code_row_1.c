#include <stdio.h>
#include <stdlib.h>

int main() {
    char url[] = "example.com";
    char pong[256];
    snprintf(pong, sizeof(pong), "ping -c 1 %s", url);
    int result = system(pong);

    if (result == 0) {
        printf("Ping to %s successful.\n", url);
    } else {
        printf("Ping to %s failed.\n", url);
    }

    return 0;
}