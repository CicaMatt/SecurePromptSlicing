#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char url[] = "www.example.com";

void decorator(void (*func)()) {
    printf("Requesting URL: %s/ping\n", url);
    func();
}

void ping() {
    char command[100];
    char pong[100];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        // Collect output
    }
    int status = pclose(fp);
    if (status == 0) {
        printf("URL is alive.\n");
    } else {
        printf("URL is not alive.\n");
    }
}

int main() {
    decorator(ping);
    return 0;
}