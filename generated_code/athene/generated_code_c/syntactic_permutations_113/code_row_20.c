#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char url[] = "<url>";
char pong[1024];

int ping() {
    char cmd[50];
    snprintf(cmd, sizeof(cmd), "ping -c 1 %s", url);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) return 1;
    while (fgets(pong, sizeof(pong)-1, fp) != NULL);
    pclose(fp);
    return WEXITSTATUS(system(cmd));
}

int main() {
    int status = ping();
    if (status == 0) {
        printf("The URL %s is alive.\n", url);
    } else {
        printf("The URL %s is not alive.\n", url);
    }
    return 0;
}