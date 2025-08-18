#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping_url(const char *url) {
    char pong[256];
    char command[512];

    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run ping.\n");
        return;
    }

    while (fgets(pong, sizeof(pong), fp) != NULL) {
        printf("%s", pong);
    }
    
    int status = pclose(fp);

    if (status == 0) {
        printf("\nThe URL %s is alive.\n", url);
    } else {
        printf("\nThe URL %s is not alive.\n", url);
    }
}

int main() {
    const char *url = "example.com";
    ping_url(url);
    return 0;
}