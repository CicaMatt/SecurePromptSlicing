#include <stdio.h>
#include <stdlib.h>

void pingFunction(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    int result = system(command);
    if (result == 0) {
        printf("pong: alive\n");
    } else {
        printf("pong: not alive\n");
    }
}

int main() {
    const char *url = "8.8.8.8"; // Example URL
    pingFunction(url);

    return 0;
}