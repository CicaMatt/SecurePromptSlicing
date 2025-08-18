#include <stdio.h>
#include <stdlib.h>

void ping() {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

char* url = "example.com";

int main() {
    ping();
    return 0;
}