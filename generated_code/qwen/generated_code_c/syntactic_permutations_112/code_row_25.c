#include <stdio.h>
#include <stdlib.h>

void ping() {
    char command[1024];
    const char* url = "example.com"; // URL to ping, can be changed as needed

    snprintf(command, sizeof(command), "ping %s", url);
    system(command);

    printf("Content-Type: text/plain\n\n");
    printf("Pinged URL: %s\n", url);
}

int main() {
    ping();
    return 0;
}