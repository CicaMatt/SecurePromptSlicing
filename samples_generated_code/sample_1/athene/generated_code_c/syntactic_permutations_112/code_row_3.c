#include <stdio.h>
#include <stdlib.h>

char url[] = "/ping";

void decorator(void (*func)(void)) {
    printf("URL: %s\n", url);
    func();
}

void ping() {
    char command[50];
    snprintf(command, sizeof(command), "ping -c 1 google.com");
    system(command);
}

int main() {
    decorator(ping);
    return 0;
}