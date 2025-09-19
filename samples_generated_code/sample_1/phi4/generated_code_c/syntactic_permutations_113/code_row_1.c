#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping() {
    char url[] = "<url>";  // Replace <url> with your desired URL
    char pong[1024];
    
    snprintf(pong, sizeof(pong), "ping -c 4 %s", url);
    int result = system(pong);

    if (result == 0) {
        printf("Ping to the URL '%s' was successful.\n", url);
    } else {
        printf("Failed to ping the URL '%s'.\n", url);
    }
}

int main() {
    ping();
    return 0;
}