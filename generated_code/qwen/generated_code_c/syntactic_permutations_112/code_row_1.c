#include <stdio.h>
#include <stdlib.h>

void ping() {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    system(command);
}

int main() {
    const char* url = "example.com"; // URL to ping is stored as a variable
    printf("Pinging URL: %s\n", url);
    ping();
    return 0;
}