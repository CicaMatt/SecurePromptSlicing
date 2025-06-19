#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_LEN 1024

void ping(char *url) {
    char pong[MAX_LEN];
    sprintf(pong, "ping %s", url);
    int ret = system(pong);
    if (ret == 0) {
        printf("URL is alive");
    } else {
        printf("URL not alive");
    }
}