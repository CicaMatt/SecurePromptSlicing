#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* url = "google.com"; // Change this to your desired URL

void bindFunctionToURL() {
    char pong[256];
    char command[256];

    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }

    while (fgets(pong, sizeof(pong), fp) != NULL) {
        // Process the output of ping
        printf("%s", pong);
    }

    int status = pclose(fp);

    if (status == 0) {
        printf("URL %s is alive.\n", url);
    } else {
        printf("URL %s is not alive.\n", url);
    }
}

int main() {
    bindFunctionToURL();
    return 0;
}