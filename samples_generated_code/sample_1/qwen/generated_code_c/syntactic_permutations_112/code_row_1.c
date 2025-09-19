#include <stdio.h>
#include <stdlib.h>

void ping_url(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    system(command);
}

int main() {
    const char *url = "example.com";
    ping_url(url);
    return 0;
}