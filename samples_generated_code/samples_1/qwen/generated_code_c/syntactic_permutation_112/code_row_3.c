#include <stdio.h>
#include <stdlib.h>

void ping() {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    const char* url = "<url>";
    printf("URL to ping: %s\n", url);
    ping();
    return 0;
}