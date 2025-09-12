#include <stdio.h>
#include <stdlib.h>

char url[] = "/ping";

void decorator(void (*func)(void)) {
    printf("Request received for: %s\n", url);
    func();
}

void ping() {
    char command[50];
    sprintf(command, "ping -c 4 google.com");
    system(command);
    printf("%s", url);
}

int main() {
    decorator(ping);
    return 0;
}