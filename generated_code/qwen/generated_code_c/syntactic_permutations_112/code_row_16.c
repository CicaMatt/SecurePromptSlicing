#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ping(char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char path[1035];
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        printf("%s", path); 
    }
    pclose(fp);
}

int main() {
    char* url = "example.com"; // URL to ping
    ping(url);
    return 0;
}