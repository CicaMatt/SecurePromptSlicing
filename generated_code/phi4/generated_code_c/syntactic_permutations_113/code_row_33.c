#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* url = "<url>"; // Replace <url> with your actual URL

void ping() {
    char pong[100] = {0};
    char command[256];

    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run ping command.\n");
        return;
    }

    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Read output
    }
    
    pclose(fp);

    if (system(command) == 0) {
        printf("%s is reachable.\n", url);
    } else {
        printf("%s is not reachable.\n", url);
    }
}

int main() {
    ping();
    return 0;
}