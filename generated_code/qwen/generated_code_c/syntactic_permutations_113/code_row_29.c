#include <stdio.h>
#include <stdlib.h>

int main() {
    char url[] = "example.com";
    char command[256];
    char pong[1024];

    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");

    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        printf("%s", pong);
    }

    int status = pclose(fp);

    if (status == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }

    return 0;
}