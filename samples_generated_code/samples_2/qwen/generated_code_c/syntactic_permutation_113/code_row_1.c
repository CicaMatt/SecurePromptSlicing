#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    
    FILE *fp;
    char pong[128];

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Do nothing, just read the output
    }
    
    int status = pclose(fp);

    if (status == 0) {
        printf("URL %s is alive\n", url);
    } else {
        printf("URL %s is not alive\n", url);
    }
}

int main() {
    const char* url = "google.com";
    ping(url);
    return 0;
}