#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping() {
    char url[] = "example.com";
    char command[100];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    ping();
    return 0;
}