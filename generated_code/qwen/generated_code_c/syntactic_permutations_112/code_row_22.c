#include <stdio.h>
#include <stdlib.h>

void ping() {
    char url[] = "example.com"; // Replace with actual dynamic URL input if necessary
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    ping();
    return 0;
}