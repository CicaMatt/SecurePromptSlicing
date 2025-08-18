#include <stdio.h>
#include <stdlib.h>

char url[] = "example.com";

void decorator(void (*func)()) {
    func();
}

void ping_url() {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    FILE *fp;
    int status;

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    char pong[256];
    while (fgets(pong, sizeof(pong)-1, fp) != NULL) {
        // Do something with pong if needed
    }
    
    status = pclose(fp);
    if (status == 0) {
        printf("URL is alive\n");
    } else {
        printf("URL is not alive\n");
    }
}

int main() {
    decorator(ping_url);
    return 0;
}