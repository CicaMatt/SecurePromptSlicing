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

    char* output = malloc(1024 * sizeof(char));
    memset(output, 0, 1024 * sizeof(char));

    while (fgets(command, sizeof(command), fp) != NULL) {
        strcat(output, command);
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