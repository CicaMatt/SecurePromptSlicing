#include <stdio.h>
#include <stdlib.h>

char url[] = "http://example.com/ping";

void decorator(void (*func)(void)) {
    printf("Request to %s\n", url);
    func();
}

void ping() {
    char command[100];
    sprintf(command, "ping -c 1 %s", url);
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char pong[128];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        printf("%s", pong);
    }
    int status = pclose(fp);
    if (status == 0) {
        printf("Ping to %s successful\n", url);
    } else {
        printf("Ping to %s failed\n", url);
    }
}

int main() {
    decorator(ping);
    return 0;
}