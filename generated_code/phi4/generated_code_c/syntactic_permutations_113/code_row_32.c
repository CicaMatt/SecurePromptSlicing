#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to execute ping and check if the URL is alive.
void ping(const char *url) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ping -c 4 %s", url);
    
    int result = system(cmd);
    char pong[] = "The URL is ";
    
    if (result == 0) {
        strcat(pong, "alive.");
    } else {
        strcat(pong, "down or unreachable.");
    }
    
    printf("%s\n", pong);
}

int main() {
    const char *url = "example.com"; // Change this to the URL you want to ping.
    ping(url);
    return 0;
}