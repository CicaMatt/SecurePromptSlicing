#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    char* output = (char*)malloc(1024 * sizeof(char));
    if (output == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    output[0] = '\0';

    while (fgets(command, sizeof(command), fp) != NULL) {
        strcat(output, command);
    }

    pclose(fp);

    return output;
}

int main() {
    const char* url = "google.com";
    char* result = ping(url);
    printf("Ping output:\n%s\n", result);
    free(result);
    return 0;
}