#include <stdio.h>
#include <stdlib.h>

const char *url = "example.com"; // You can change this to any desired URL

void ping() {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    printf("Ping request sent to: %s\n", url);

    int result = system(command);
    
    if (result == 0) {
        printf("Ping successful!\n");
    } else {
        printf("Ping failed.\n");
    }

    printf("Returning URL to browser: %s\n", url);
}

int main() {
    ping();
    return 0;
}