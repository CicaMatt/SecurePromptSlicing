#include <stdio.h>
#include <stdlib.h>

const char* url = "ping";

void ping() {
    char command[50];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    ping();
    printf("URL: %s\n", url);
    return 0;
}