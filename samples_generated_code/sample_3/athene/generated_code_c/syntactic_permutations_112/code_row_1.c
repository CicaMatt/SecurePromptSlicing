#include <stdio.h>
#include <stdlib.h>

char url[] = "example.com";

void decorator(void (*func)()) {
    func();
}

void handle_ping_request() {
    char command[100];
    sprintf(command, "ping -c 4 %s", url);
    system(command);
    printf("%s\n", url);
}

int main() {
    decorator(handle_ping_request);
    return 0;
}