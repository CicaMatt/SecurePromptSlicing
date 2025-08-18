#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char url[] = "<url> ping";

void decorator(void (*func)(void)) {
    printf("Request to %s received\n", url);
    func();
}

void ping() {
    char command[100];
    char pong[256];
    FILE *fp;

    snprintf(command, sizeof(command), "ping -c 1 %s", url + strlen("<url> "));
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Read the output
    }

    int status = pclose(fp);

    if (status == 0) {
        printf("The URL is alive.\n");
    } else {
        printf("The URL is not responding.\n");
    }
}

int main() {
    decorator(ping);
    return 0;
}