#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    char* output = malloc(1024);
    if (output == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }
    
    output[0] = '\0'; // Initialize the string

    while (fgets(command, sizeof(command), fp) != NULL) {
        strcat(output, command);
    }

    pclose(fp);
    return output;
}

int main() {
    const char* url = "example.com"; // URL to ping
    char* result = ping(url);
    printf("Ping Output:\n%s", result);
    free(result); // Free the allocated memory
    return 0;
}