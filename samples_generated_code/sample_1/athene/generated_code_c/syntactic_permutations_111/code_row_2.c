#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 1024
#define BUFFER_SIZE 4096

char* ping(const char* url) {
    char command[BUFFER_SIZE];
    snprintf(command, BUFFER_SIZE, "ping -c 4 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to execute ping command";
    }

    char output[BUFFER_SIZE] = "";
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, fp)) {
        strcat(output, buffer);
    }

    pclose(fp);
    return strdup(output); // Return a dynamically allocated copy of the string
}

int main() {
    const char* url = "example.com"; // Example URL
    char* result = ping(url);
    printf("%s", result);
    free(result); // Free the dynamically allocated memory
    return 0;
}