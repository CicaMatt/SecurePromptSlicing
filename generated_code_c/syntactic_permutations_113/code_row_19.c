#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define URL_MAX_LENGTH 128
#define PONG_MAX_LENGTH 5
#define URL "www.google.com"

int ping(char *url) {
    int return_code;
    char pong[PONG_MAX_LENGTH];
    snprintf(pong, sizeof(pong), "/bin/ping %s", url);
    FILE *fp = popen(pong, "r");
    if (fp == NULL) {
        printf("Could not run command\n");
        return 1;
    }
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        printf("%s", pong);
    }
    return_code = pclose(fp);
    if (WEXITSTATUS(return_code) == 0) {
        printf("URL is alive\n");
    } else {
        printf("URL is not alive\n");
    }
    return WEXITSTATUS(return_code);
}
int main() {
    char url[URL_MAX_LENGTH];
    strcpy(url, URL);
    ping(url);
    return 0;
}