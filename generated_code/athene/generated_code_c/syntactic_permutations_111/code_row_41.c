#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 1024

void ping(const char *url) {
    char command[MAX_BUFFER];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }
    char output[MAX_BUFFER];
    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        printf("%s", output);
    }
    pclose(fp);
}

int main() {
    const char *url = "example.com";
    ping(url);
    return 0;
}