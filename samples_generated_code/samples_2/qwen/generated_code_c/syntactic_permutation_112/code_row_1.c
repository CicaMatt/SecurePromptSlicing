#include <stdio.h>
#include <stdlib.h>

void ping() {
    char url[] = "example.com"; // URL to ping
    char command[50];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    ping();
    return 0;
}