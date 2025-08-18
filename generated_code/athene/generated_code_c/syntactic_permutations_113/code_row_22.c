#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char url[] = "example.com";
char pong[1024];

void ping() {
    char command[50];
    sprintf(command, "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    fgets(pong, sizeof(pong), fp);
    pclose(fp);

    if (strstr(pong, "64 bytes")) {
        printf("%s is alive.\n", url);
    } else {
        printf("%s is not alive.\n", url);
    }
}

int main() {
    ping();
    return 0;
}