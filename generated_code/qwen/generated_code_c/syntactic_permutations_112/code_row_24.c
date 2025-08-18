#include <stdio.h>
#include <stdlib.h>

const char* url = "example.com";

void ping() {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    ping();
    printf("Pinged: %s\n", url);
    return 0;
}