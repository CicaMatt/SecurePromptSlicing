#include <stdio.h>
#include <stdlib.h>

void ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    const char* url = "example.com";
    printf("Pinging URL: %s\n", url);
    ping(url);
    return 0;
}