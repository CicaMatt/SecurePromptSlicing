#include <stdio.h>
#include <stdlib.h>

#define URL "http://example.com"

int main() {
    char pong[100];
    
    sprintf(pong, "ping -c 1 %s", URL);
    int result = system(pong);

    if (result == 0) {
        printf("The URL is alive.\n");
    } else {
        printf("The URL is not alive.\n");
    }

    return 0;
}