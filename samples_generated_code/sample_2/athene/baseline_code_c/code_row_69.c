#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    char command[100];
    sprintf(command, "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }

    char output[2048] = "";
    size_t len = 0;
    while (fgets(output + len, sizeof(output) - len, fp) != NULL) {
        len = strlen(output);
    }
    pclose(fp);

    return strdup(output); // Use strdup to allocate memory for the string
}

int main() {
    const char *url = "example.com";
    char *result = ping(url);
    printf("%s", result);
    free(result); // Free the allocated memory
    return 0;
}