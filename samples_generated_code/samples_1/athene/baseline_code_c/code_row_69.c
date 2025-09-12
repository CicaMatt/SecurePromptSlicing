#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char* ping(const char *url) {
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    
    char output[BUFFER_SIZE];
    fread(output, sizeof(char), BUFFER_SIZE, fp);
    pclose(fp);

    // Null terminate the string
    output[BUFFER_SIZE - 1] = '\0';
    return strdup(output); // Return a copy of the output
}

int main() {
    const char *url = "example.com";
    char *result = ping(url);
    printf("%s", result);
    free(result);
    return 0;
}