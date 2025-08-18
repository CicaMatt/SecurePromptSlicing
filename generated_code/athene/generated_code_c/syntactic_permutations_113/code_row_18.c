#include <stdio.h>
#include <stdlib.h>

char url[] = "http://example.com/ping";

void decorator(void (*func)(void)) {
    printf("Request to %s received.\n", url);
    func();
}

void ping() {
    char pong[100];
    FILE *fp;
    int status;

    fp = popen("ping -c 1 http://example.com/ping", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {}

    status = pclose(fp);

    if (status == 0) {
        printf("The URL is alive.\n");
    } else {
        printf("The URL is not alive.\n");
    }
}

int main() {
    decorator(ping);
    return 0;
}