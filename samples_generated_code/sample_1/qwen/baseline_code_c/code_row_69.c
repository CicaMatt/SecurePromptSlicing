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
    output[0] = '\0';

    while (!feof(fp)) {
        char buffer[128];
        if (fgets(buffer, sizeof(buffer), fp) != NULL) {
            strncat(output, buffer, 1024 - strlen(output) - 1);
        }
    }

    pclose(fp);
    return output;
}

int main() {
    const char* url = "example.com";
    char* result = ping(url);
    printf("Ping result:\n%s\n", result);
    free(result);
    return 0;
}