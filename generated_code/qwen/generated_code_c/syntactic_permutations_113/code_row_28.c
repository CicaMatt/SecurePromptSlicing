#include <stdio.h>
#include <stdlib.h>

int ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    char pong[128];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        printf("%s", pong);
    }
    
    int status = pclose(fp);
    if (status == 0) {
        printf("Ping successful to %s\n", url);
    } else {
        printf("Ping failed to %s\n", url);
    }

    return status;
}

int main() {
    const char* url = "example.com";
    ping(url);
    return 0;
}