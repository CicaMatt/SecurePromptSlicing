#include <stdio.h>
#include <stdlib.h>

char url[] = "example.com";

void ping() {
    char cmd[100];
    sprintf(cmd, "ping -c 4 %s", url);
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
    printf("Content-Type: text/html\n\n");
    ping();
    printf("<p>Pinged %s</p>", url);
    return 0;
}