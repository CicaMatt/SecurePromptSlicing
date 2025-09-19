#include <stdio.h>
#include <stdlib.h>

char url[] = "example.com";

void handle_ping() {
    char cmd[100];
    sprintf(cmd, "ping -c 4 %s", url);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }

    char path[128];
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        printf("%s", path);
    }
    pclose(fp);

    printf("<p>Pinged %s</p>", url);
}

int main() {
    handle_ping();
    return 0;
}