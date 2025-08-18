#include <stdio.h>
#include <stdlib.h>

char* ping(char *url) {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to execute ping command";
    }
    char output[500];
    fgets(output, sizeof(output) - 1, fp);
    pclose(fp);
    return strdup(output); // Return a copy of the output
}

int main() {
    char *url = "example.com"; // Example URL
    char *result = ping(url);
    printf("%s\n", result);
    free(result); // Free the allocated memory for the output
    return 0;
}