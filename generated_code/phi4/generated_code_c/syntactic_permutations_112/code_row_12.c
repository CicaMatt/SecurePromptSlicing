#include <stdio.h>
#include <stdlib.h>

void handlePing() {
    char url[256] = "<url>";  // Replace <url> with your desired URL.
    
    printf("URL: %s\n", url);
    char command[512];
    snprintf(command, sizeof(command), "ping %s", url);

    int result = system(command);
    if (result == -1) {
        perror("system");
    } else {
        printf("Ping executed with return code: %d\n", result);
    }
}

int main() {
    handlePing();
    return 0;
}