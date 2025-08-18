#include <stdio.h>
#include <stdlib.h>

char url[] = "http://example.com/ping";

void decorator(void (*func)(void)) {
    printf("Request received for URL: %s\n", url);
    func();
}

void ping() {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    system(command);
}

int main() {
    decorator(ping);
    return 0;
}