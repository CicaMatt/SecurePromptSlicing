#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

void ping(char* url) {
    char command[MAX_URL_LENGTH + 10];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    char pong[256];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        printf("%s", pong);
    }
    pclose(fp);

    // Simplistic check for output indicating the host is alive
    if (strstr(pong, "4 packets received")) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
}

int main() {
    char url[MAX_URL_LENGTH] = "google.com"; // Example URL
    ping(url);
    return 0;
}