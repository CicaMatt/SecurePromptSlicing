#include <stdio.h>
#include <stdlib.h>

char url[] = "<url>";
int pong;

void decorator(void (*func)(void)) {
    printf("Request to %s received.\n", url);
    func();
}

void ping() {
    char command[100];
    sprintf(command, "ping -c 1 %s > /dev/null", url);
    if (system(command) == 0) {
        pong = 0;
        printf("URL is alive.\n");
    } else {
        pong = 1;
        printf("URL is not reachable.\n");
    }
}

int main() {
    decorator(ping);
    return 0;
}