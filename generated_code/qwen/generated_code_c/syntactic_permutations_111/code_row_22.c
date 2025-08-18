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

    char* output = malloc(1024);
    if (output == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    while (fgets(output, 1024, fp) != NULL) {
        printf("%s", output);
    }

    pclose(fp);
    return output;
}

int main() {
    const char* url = "google.com";
    char* result = ping(url);
    free(result);
    return 0;
}