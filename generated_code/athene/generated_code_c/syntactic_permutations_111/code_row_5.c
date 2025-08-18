#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 1024

char* ping(char* url) {
    char command[MAX_BUFFER];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    char output[MAX_BUFFER];
    fgets(output, sizeof(output), fp);
    pclose(fp);
    return strdup(output); // Duplicate the string as it will be destroyed when function returns
}

int main() {
    char* url = "example.com";
    char* result = ping(url);
    printf("%s\n", result);
    free(result); // Free the duplicated string
    return 0;
}