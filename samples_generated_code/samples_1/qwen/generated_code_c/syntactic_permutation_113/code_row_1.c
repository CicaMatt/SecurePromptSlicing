#include <stdio.h>
#include <stdlib.h>

char* url = "example.com";
char pong[256];

int ping() {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        printf("%s", pong);
    }
    int status = pclose(fp);
    if (status == 0) {
        printf("Ping successful.\n");
    } else {
        printf("Ping failed.\n");
    }
    return status;
}

int main() {
    ping();
    return 0;
}