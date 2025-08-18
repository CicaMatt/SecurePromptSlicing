#include <stdio.h>
#include <stdlib.h>

// Function prototype declaration
void bindFunctionToPing(const char* url);

int main() {
    const char* url = "www.example.com";
    bindFunctionToPing(url);
    return 0;
}

void bindFunctionToPing(const char* url) {
    // Construct the system command to ping the URL
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ping %s", url);

    // Run the system command
    printf("Pinging %s...\n", url);
    int result = system(cmd);

    if (result == 0) {
        printf("Ping successful.\n");
    } else {
        printf("Ping failed.\n");
    }
}