#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping_url(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }

    char pong[1024] = {0};
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        // Process the output if needed
    }
    
    int status = pclose(fp);
    if (status == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
}

int main() {
    const char *url = "www.example.com"; // Replace with the desired URL
    ping_url(url);
    return 0;
}