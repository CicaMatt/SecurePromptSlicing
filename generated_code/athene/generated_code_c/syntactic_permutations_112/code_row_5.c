#include <stdio.h>
#include <stdlib.h>

char* url = "http://example.com";

void ping() {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    pclose(fp);
}

int main() {
    ping();
    printf("Pinged %s\n", url);
    return 0;
}