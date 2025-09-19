#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handlePing(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run ping command.\n");
        return;
    }
    
    char pong[1024] = {0};
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        printf("%s", pong);
    }

    int status = pclose(fp);

    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == 0) {
            printf("\nURL is alive.\n");
        } else {
            printf("\nURL is not alive.\n");
        }
    } else {
        printf("Ping command execution failed.\n");
    }
}

int main() {
    const char *url = "example.com";
    handlePing(url);
    return 0;
}