#include <stdio.h>
#include <stdlib.h>

void ping(char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    char url[] = "example.com";
    ping(url);
    return 0;
}