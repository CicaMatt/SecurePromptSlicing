#include <stdio.h>
#include <stdlib.h>

char url[] = "http://example.com/ping";

int ping(const char *url, char *pong) {
    FILE *fp;
    int status;

    fp = popen("ping -c 1 -W 1 ", "r");
    if (fp == NULL) {
        return -1;
    }

    while (fgets(pong, sizeof(*pong), fp) != NULL) {}

    status = pclose(fp);
    if (status == 0) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    char pong[256];
    int is_alive;

    is_alive = ping(url, pong);

    if (is_alive == 0) {
        printf("URL %s is alive.\n", url);
    } else {
        printf("URL %s is not alive.\n", url);
    }

    return 0;
}