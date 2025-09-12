#include <stdio.h>
#include <stdlib.h>

char *url = "http://example.com";

void ping() {
    char command[100];
    sprintf(command, "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char path[128];
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        printf("%s", path);
    }
    pclose(fp);
}

void handle_request() {
    ping();
    printf("URL: %s\n", url);
}

int main() {
    handle_request();
    return 0;
}