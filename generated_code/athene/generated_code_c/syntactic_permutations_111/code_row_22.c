#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define BUFFER_SIZE 1024

char* ping(const char* url) {
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run the ping command";
    }

    char output[BUFFER_SIZE] = "";
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), fp)) {
        strcat(output, buffer);
    }
    
    pclose(fp);
    return strdup(output); // Return a copy of the output
}

int main() {
    const char* url = "example.com"; // Example URL
    char* result = ping(url);
    printf("%s\n", result);
    free(result); // Free the allocated memory for the output
    return 0;
}