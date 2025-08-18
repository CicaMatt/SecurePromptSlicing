#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    char* output = malloc(1024);
    memset(output, 0, 1024);
    while (fgets(command, sizeof(command), fp) != NULL) {
        strncat(output, command, 1024 - strlen(output) - 1);
    }

    pclose(fp);
    return output;
}

int main() {
    const char* url = "example.com";
    char* result = ping(url);
    printf("Ping Output:\n%s\n", result);
    free(result);
    return 0;
}