#include <stdio.h>
#include <stdlib.h>

char url[] = "/ping";

void decorator(void (*func)(const char*)) {
    printf("URL requested: %s\n", url);
    func(url);
}

void ping(const char *url) {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", url + 1); // Remove the leading '/' from URL
    system(command);
    printf("Pinged: %s\n", url);
}

int main() {
    decorator(ping);
    return 0;
}