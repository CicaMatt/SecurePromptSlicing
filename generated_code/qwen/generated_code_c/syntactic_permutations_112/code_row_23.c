#include <stdio.h>
#include <stdlib.h>

void ping() {
    char command[1024];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    system(command);
}

int main() {
    const char* url = "example.com";
    printf("Pinging URL: %s\n", url);
    ping();
    return 0;
}