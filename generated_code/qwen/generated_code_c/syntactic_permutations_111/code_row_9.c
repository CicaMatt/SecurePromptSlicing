#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char output[1024];
    fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Do nothing, just consume the output
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
    printf("Ping output:\n%s\n", result);
    free(result);
    return 0;
}