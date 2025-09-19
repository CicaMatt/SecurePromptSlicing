#include <stdio.h>
#include <stdlib.h>

#define MAX_OUTPUT 1024

char* ping(const char *url) {
    char command[50];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    char output[MAX_OUTPUT] = "";
    while (fgets(output + strlen(output), sizeof(output) - strlen(output), fp) != NULL);
    pclose(fp);
    return strdup(output); // Use strdup to dynamically allocate memory for the string
}

int main() {
    const char *url = "example.com";
    char *result = ping(url);
    printf("%s", result);
    free(result); // Free the allocated memory
    return 0;
}