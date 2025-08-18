#include <stdio.h>
#include <stdlib.h>

char *url = "http://example.com/ping";

void decorator(void (*func)()) {
    printf("URL: %s\n", url);
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