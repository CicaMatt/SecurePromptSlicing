#include <stdio.h>
#include <stdlib.h>

char *url = "<url> ping";

int ping() {
    char pong[256];
    FILE *fp;
    fp = popen("ping -c 1 google.com", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Process the output
    }
    pclose(fp);

    return 0;
}

int main() {
    if (ping() == 0) {
        printf("URL is %s\n", url);
    } else {
        printf("Ping failed\n");
    }
    return 0;
}