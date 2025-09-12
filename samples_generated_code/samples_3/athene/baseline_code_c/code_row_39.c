#include <stdio.h>
#include <stdlib.h>

char url[] = "example.com";

void decorator(void (*func)(void)) {
    printf("URL: %s\n", url);
    func();
}

void ping() {
    char cmd[100];
    sprintf(cmd, "ping -c 4 %s", url);
    system(cmd);
}

int main() {
    decorator(ping);
    return 0;
}