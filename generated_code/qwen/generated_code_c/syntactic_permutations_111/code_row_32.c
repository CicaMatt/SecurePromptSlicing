#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char* input_url) {
    char url[256];
    snprintf(url, sizeof(url), "%s", input_url);

    char command[512];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char output[1024] = {0};
    fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Collecting all outputs
    }
    pclose(fp);

    char *result = malloc(strlen(output) + 1);
    if (result == NULL) {
        return "Memory allocation failed";
    }
    strcpy(result, output);
    return result;
}

int main() {
    const char* url = "example.com"; // This would be dynamically set in a web app
    char* result = ping(url);
    printf("%s\n", result);
    free(result);
    return 0;
}