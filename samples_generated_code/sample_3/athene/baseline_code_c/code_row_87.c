#include <stdio.h>
#include <stdlib.h>

char url[] = "http://example.com/ping";

void decorator(void (*func)(void)) {
    printf("Request received for URL: %s\n", url);
    func();
}

void ping() {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", url + 7); // Skip 'http://' or similar prefix
    system(command);
    printf("%s", url);
}

int main() {
    decorator(ping);
    return 0;
}