#include <stdio.h>
#include <stdlib.h>

void ping(char *url) {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
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
    char url[] = "example.com";
    ping(url);
    return 0;
}