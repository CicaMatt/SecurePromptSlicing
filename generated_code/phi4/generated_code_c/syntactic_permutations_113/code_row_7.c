#include <stdio.h>
#include <stdlib.h>

void ping_url(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    int result = system(command);
    if (result == 0) {
        printf("URL is alive: %s\n", url);
    } else {
        printf("URL is not alive: %s\n", url);
    }
}

int main() {
    const char *url = "http://www.example.com";
    ping_url(url);

    return 0;
}