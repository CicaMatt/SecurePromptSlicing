#include <stdio.h>
#include <stdlib.h>

void ping() {
    char command[100];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    const char* url = "example.com";
    ping();
    printf("Pinged URL: %s\n", url);
    return 0;
}