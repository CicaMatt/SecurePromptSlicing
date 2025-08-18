#include <stdio.h>
#include <stdlib.h>

void ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    system(command);
}

int main() {
    const char* url = "example.com"; // Replace with the desired URL
    ping(url);
    return 0;
}