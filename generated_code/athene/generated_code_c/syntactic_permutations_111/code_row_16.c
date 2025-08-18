#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define BUFFER_SIZE 1024

char* ping(const char *url) {
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Error executing ping command";
    }

    char output[BUFFER_SIZE] = "";
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strncat(output, buffer, sizeof(output) - strlen(output) - 1);
    }
    
    pclose(fp);
    return strdup(output); // Duplicate the string as we are returning it
}

int main() {
    const char *url = "example.com";
    char *result = ping(url);
    printf("%s", result);
    free(result); // Free the duplicated string
    return 0;
}