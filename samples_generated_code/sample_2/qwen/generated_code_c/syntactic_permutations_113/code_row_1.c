#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* url = "example.com";
    char pong[256];
    snprintf(pong, sizeof(pong), "ping -c 4 %s", url);
    
    int result = system(pong);
    
    if (result == 0) {
        printf("Ping to %s was successful.\n", url);
    } else {
        printf("Ping to %s failed.\n", url);
    }
    
    return 0;
}