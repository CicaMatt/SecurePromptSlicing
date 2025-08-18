#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char* ping(const char* url) {
    char command[BUFFER_SIZE];
    char *output = (char*)malloc(BUFFER_SIZE * sizeof(char));
    FILE *fp;

    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        free(output);
        return NULL;
    }

    while (fgets(output, BUFFER_SIZE, fp) != NULL) {
        // Do nothing, just read the output
    }

    pclose(fp);
    return output;
}

int main() {
    const char* url = "example.com"; // URL to ping
    char* result = ping(url);

    if (result != NULL) {
        printf("Ping output:\n%s", result);
        free(result);
    }

    return 0;
}