#include <stdio.h>
#include <stdlib.h>

void ping_url(char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    char url[] = "example.com";
    printf("Pinging URL: %s\n", url);
    ping_url(url);
    return 0;
}