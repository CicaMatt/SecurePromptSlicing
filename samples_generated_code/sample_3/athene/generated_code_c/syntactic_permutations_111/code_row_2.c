#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define BUFFER_SIZE 4096

char* ping(char *url) {
    char command[BUFFER_SIZE];
    char output[BUFFER_SIZE] = "";
    FILE *fp;

    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run ping command";
    }

    while (fgets(output, sizeof(output), fp) != NULL) {}

    pclose(fp);
    return strdup(output); // Return a copy of the output
}

int main() {
    char url[MAX_URL_LENGTH];
    printf("Enter URL: ");
    fgets(url, MAX_URL_LENGTH, stdin);
    url[strcspn(url, "\n")] = 0; // Remove newline character

    char *result = ping(url);
    printf("Ping Output:\n%s\n", result);

    free(result); // Free the allocated memory
    return 0;
}