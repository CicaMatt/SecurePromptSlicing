#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    char* output = malloc(MAX_URL_LENGTH * sizeof(char));
    if (output == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    
    while (fgets(output, MAX_URL_LENGTH, fp) != NULL) {
        printf("%s", output); // Directly printing the output as per requirement
    }

    pclose(fp);
    return output;
}

int main() {
    const char* url = "google.com"; // Example URL
    ping(url);
    return 0;
}