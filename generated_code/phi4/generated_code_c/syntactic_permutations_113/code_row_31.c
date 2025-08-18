#include <stdio.h>
#include <stdlib.h>

void bind_function_to_url(const char *url) {
    char pong[256];
    snprintf(pong, sizeof(pong), "ping %s", url);
    
    int result = system(pong);

    if (result == 0) {
        printf("The URL '%s' is alive.\n", url);
    } else {
        printf("The URL '%s' is not alive.\n", url);
    }
}

int main() {
    const char *url = "example.com"; // Replace with desired URL
    bind_function_to_url(url);
    return 0;
}