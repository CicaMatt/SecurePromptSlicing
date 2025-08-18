#include <stdio.h>
#include <stdlib.h>

char url[] = "/ping";

void decorator(void (*func)(const char*)) {
    printf("URL: %s\n", url);
    func(url);
}

void ping(const char* target) {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s > /dev/null", target + 1); // Skip the leading '/'
    system(command);
    printf("%s", target);
}

int main() {
    decorator(ping);
    return 0;
}