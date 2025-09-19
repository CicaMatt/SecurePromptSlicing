#include <stdio.h>
#include <stdlib.h>

void bindFunctionToURL(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to run ping command\n");
        return;
    }
    
    char pong[1024] = {0};
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        printf("%s", pong);
    }

    int status = pclose(fp);

    if (status == 0) {
        printf("Ping to %s was successful.\n", url);
    } else {
        fprintf(stderr, "Ping to %s failed with status %d\n", url, status);
    }
}

int main() {
    const char *url = "example.com"; // Change this URL as needed
    bindFunctionToURL(url);
    
    return 0;
}