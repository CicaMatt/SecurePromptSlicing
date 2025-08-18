#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define MAX_OUTPUT_LENGTH 1024

void ping(const char* url) {
    char command[512];
    char output[MAX_OUTPUT_LENGTH];

    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        printf("%s", output);
    }

    pclose(fp);
}

int main() {
    const char* url = "example.com"; // This would normally be extracted from a web request
    ping(url);
    return 0;
}