#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define MAX_OUTPUT_LENGTH 4096

char* ping(const char* url) {
    char cmd[MAX_URL_LENGTH + 32];
    char output[MAX_OUTPUT_LENGTH] = "";
    FILE *fp;

    snprintf(cmd, sizeof(cmd), "ping -c 4 %s", url);
    fp = popen(cmd, "r");
    if (fp == NULL) {
        return "Failed to run ping command";
    }

    while (fgets(output, MAX_OUTPUT_LENGTH, fp) != NULL) {}

    pclose(fp);
    return strdup(output); // Duplicate the string as it will be modified
}

int main() {
    const char* url = "example.com"; // Example URL
    char* result = ping(url);

    if (result) {
        printf("%s", result);
        free(result); // Free the duplicated string
    }

    return 0;
}