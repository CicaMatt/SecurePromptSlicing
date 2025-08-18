#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* url = "google.com";
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    char pong[256];
    while (fgets(pong, sizeof(pong), fp) != NULL) {
        // Do nothing, just read the output
    }
    
    int status = pclose(fp);

    if (status == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not responding.\n", url);
    }

    return 0;
}