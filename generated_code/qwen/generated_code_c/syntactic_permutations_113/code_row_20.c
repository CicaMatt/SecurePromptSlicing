#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256

int ping(const char *url) {
    char command[MAX_URL_LENGTH + 10];
    snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", url);
    int result = system(command);
    return result == 0;
}

int main() {
    const char *url = "example.com";
    int is_alive = ping(url);
    
    if (is_alive) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }

    return 0;
}