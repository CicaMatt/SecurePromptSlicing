#include <stdio.h>
#include <stdlib.h>

char* ping(char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    char* output = malloc(1024);
    if (output == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    output[0] = '\0';

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(output, buffer);
    }

    pclose(fp);

    return output;
}

int main() {
    char* url = "google.com";
    char* result = ping(url);
    printf("%s", result);
    free(result);
    return 0;
}