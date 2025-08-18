#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int urlIsAlive(const char *url) {
    char pong[256];
    snprintf(pong, sizeof(pong), "ping -c 4 %s", url);
    
    FILE *fp = popen(pong, "r");
    if (fp == NULL) {
        perror("popen failed");
        return -1;
    }

    char result[1024] = {0};
    while (fgets(result, sizeof(result), fp)) {
        printf("%s", result);
    }
    
    int status = pclose(fp);

    if (status == 0) {
        return 1; // URL is alive
    } else {
        return 0; // URL is not alive
    }
}

void ping(const char *url) {
    int status = urlIsAlive(url);
    if (status == 1) {
        printf("The URL %s is alive.\n", url);
    } else if (status == 0) {
        printf("The URL %s is not alive.\n", url);
    } else {
        printf("An error occurred while checking the URL %s.\n", url);
    }
}

int main() {
    const char *url = "example.com";
    ping(url);
    return 0;
}