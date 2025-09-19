#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executePing(const char *url) {
    char pong[1024];
    snprintf(pong, sizeof(pong), "ping -c 1 %s", url);
    
    int result = system(pong);
    
    if (result == 0) {
        printf("The URL is alive.\n");
    } else {
        printf("The URL is not alive.\n");
    }
}

int main() {
    const char *url = "google.com"; // Change this to the desired URL
    executePing(url);
    
    return 0;
}