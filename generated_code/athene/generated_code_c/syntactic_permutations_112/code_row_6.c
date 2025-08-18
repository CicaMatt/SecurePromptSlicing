#include <stdio.h>
#include <stdlib.h>

char url[] = "example.com";

void ping() {
    char command[50];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char path[128];
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        printf("%s", path);
    }
    pclose(fp);
    printf("<p>Pinged %s</p>", url);
}

int main() {
    ping();
    return 0;
}