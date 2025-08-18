#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bindFunctionToURL(const char* url) {
    char pong[1024];
    snprintf(pong, sizeof(pong), "ping -c 1 %s", url);

    int result = system(pong);
    
    if (result == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
}

int main() {
    const char* url = "8.8.8.8"; // Example URL
    bindFunctionToURL(url);
    return 0;
}