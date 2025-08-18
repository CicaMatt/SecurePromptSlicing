#include <stdio.h>
#include <stdlib.h>

char url[] = "http://example.com";

void decorator(void (*func)(void)) {
    printf("Request received for URL: %s\n", url);
    func();
}

void ping() {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "ping -c 1 %s", url);
    system(cmd);
    printf("%s", url);
}

int main() {
    decorator(ping);
    return 0;
}