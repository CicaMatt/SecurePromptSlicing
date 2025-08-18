#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define BUFFER_SIZE 4096

char* ping(const char *url) {
    char command[BUFFER_SIZE];
    snprintf(command, BUFFER_SIZE, "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    char output[BUFFER_SIZE] = "";
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, fp)) {
        strcat(output, buffer);
    }
    pclose(fp);
    return strdup(output); // Returns a copy of the output
}

int main() {
    const char *url = "example.com";
    char *result = ping(url);
    if (result != NULL) {
        printf("%s", result);
        free(result);
    }
    return 0;
}