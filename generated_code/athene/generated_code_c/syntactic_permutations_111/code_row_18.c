#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define MAX_OUTPUT_LENGTH 4096

char* ping(char *url) {
    char command[MAX_URL_LENGTH + 64];
    char output[MAX_OUTPUT_LENGTH] = "";
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run ping command";
    }
    while (fgets(output, sizeof(output), fp)) {}
    pclose(fp);
    return strdup(output); // Duplicate the string as it will be modified
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    scanf("%1023s", url); // Read URL from user input for testing purposes

    char *result = ping(url);
    printf("Ping output:\n%s\n", result);

    free(result); // Free the allocated memory
    return 0;
}