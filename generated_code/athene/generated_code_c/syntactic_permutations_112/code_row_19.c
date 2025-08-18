#include <stdio.h>
#include <stdlib.h>

char url[] = "example.com";

void decorator(void (*func)(void)) {
    printf("Request received for URL: %s/ping\n", url);
    func();
}

void ping() {
    char command[100];
    sprintf(command, "ping -c 4 %s", url);
    system(command);
}

int main() {
    decorator(ping);
    return 0;
}