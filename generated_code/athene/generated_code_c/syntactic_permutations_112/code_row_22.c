#include <stdio.h>
#include <stdlib.h>

char url[] = "http://example.com/ping";

void ping() {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "ping -c 4 %s", url);
    FILE *fp = popen(cmd, "r");
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

int main() {
    ping();
    return 0;
}