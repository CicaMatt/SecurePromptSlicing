#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char buffer[BUFFER_SIZE];
    char *output = malloc(BUFFER_SIZE);
    output[0] = '\0';

    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strncat(output, buffer, BUFFER_SIZE - strlen(output) - 1);
    }

    pclose(fp);

    return output;
}

int main() {
    const char* url = "8.8.8.8"; // Example URL
    char* result = ping(url);
    printf("Ping output:\n%s\n", result);
    free(result);
    return 0;
}