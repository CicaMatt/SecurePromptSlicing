#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 256
#define PING_COMMAND_FORMAT "ping -c 1 %s > /dev/null 2>&1"

void ping(const char* url) {
    char command[MAX_URL_LENGTH + sizeof(PING_COMMAND_FORMAT) - 3]; // -3 for format placeholders
    snprintf(command, sizeof(command), PING_COMMAND_FORMAT, url);

    int result = system(command);
    if (result == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
}

int main() {
    const char* url = "example.com";
    ping(url);
    return 0;
}