#include <stdio.h>
#include <stdlib.h>

char url[] = "http://example.com/ping";

void decorator(void (*func)()) {
    printf("URL requested: %s\n", url);
    func();
}

void ping() {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "ping -c 4 %s", url); // Adjust the command as needed
    system(cmd);
    printf("%s", url);
}

int main() {
    decorator(ping);
    return 0;
}