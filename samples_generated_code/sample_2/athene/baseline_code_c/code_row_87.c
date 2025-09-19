#include <stdio.h>
#include <stdlib.h>

char url[] = "http://example.com/ping";

void decorator(void (*func)()) {
    printf("Request received for: %s\n", url);
    func();
}

void ping() {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "ping -c 4 %s", url);
    system(cmd);
    printf("%s\n", url);
}

int main() {
    decorator(ping);
    return 0;
}