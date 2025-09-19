#include <stdio.h>
#include <stdlib.h>

void ping(char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    char url[] = "example.com";
    printf("Pinging URL: %s\n", url);
    ping(url);
    return 0;
}