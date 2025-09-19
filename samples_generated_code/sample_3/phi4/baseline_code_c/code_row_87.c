#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executePing(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    printf("Executing: %s\n", command);
    int result = system(command);

    if (result == 0) {
        printf("Ping to %s successful.\n", url);
    } else {
        printf("Ping to %s failed.\n", url);
    }
}

int main() {
    const char *url = "8.8.8.8"; // Example URL, replace with desired address

    executePing(url);

    return 0;
}