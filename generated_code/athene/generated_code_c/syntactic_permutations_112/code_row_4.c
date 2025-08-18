#include <stdio.h>
#include <stdlib.h>

char url[] = "http://example.com/ping";

void ping() {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char path[1024];
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        printf("%s", path);
    }
    pclose(fp);
}

int main() {
    ping();
    printf("URL: %s\n", url);
    return 0;
}