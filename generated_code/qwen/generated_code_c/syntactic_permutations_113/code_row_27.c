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

    char pong[1024];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        printf("%s", pong);
    }
    
    int status = pclose(fp);
    if (status == 0) {
        printf("Ping to %s was successful.\n", url);
    } else {
        printf("Ping to %s failed.\n", url);
    }

    return status;
}

int main() {
    const char* url = "google.com";
    ping(url);
    return 0;
}