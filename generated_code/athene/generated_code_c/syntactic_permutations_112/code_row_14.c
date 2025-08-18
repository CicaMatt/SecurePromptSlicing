#include <stdio.h>
#include <stdlib.h>

char url[] = "/ping";

void decorator(char *path, void (*func)()) {
    if (strcmp(path, url) == 0) {
        func();
    }
}

void ping() {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "ping -c 4 google.com");
    FILE *fp = popen(cmd, "r");
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
    decorator(url, ping);
    return 0;
}