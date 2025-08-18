#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

int ping(const char* url, char* pong) {
    char command[MAX_URL_LENGTH + 10];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        strcpy(pong, "Error opening pipe for ping command.");
        return -1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(pong, buffer);
    }
    pclose(fp);

    // Simple check if the ping was successful
    if (strstr(pong, "bytes from") != NULL) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    const char* url = "google.com";
    char pong[1024] = "";

    int result = ping(url, pong);
    if (result == 0) {
        printf("URL %s is alive.\n", url);
    } else {
        printf("URL %s is not alive.\n", url);
    }

    printf("Ping output:\n%s\n", pong);

    return 0;
}