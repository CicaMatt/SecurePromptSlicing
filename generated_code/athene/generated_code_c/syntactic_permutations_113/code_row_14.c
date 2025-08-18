#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *url = "<url>";

void decorator(void (*func)(const char *)) {
    func(url);
}

void ping(const char *target) {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 1 %s", target);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    
    char pong[1024];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Collect the output
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