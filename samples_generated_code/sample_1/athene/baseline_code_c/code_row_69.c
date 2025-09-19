#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 1024

char* ping(const char *url) {
    char command[MAX_BUFFER];
    snprintf(command, sizeof(command), "ping -c 1 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }

    char output[MAX_BUFFER];
    fgets(output, sizeof(output), fp);

    pclose(fp);
    return strdup(output); // Duplicate the string as it will be used after function returns
}

int main() {
    const char *url = "example.com"; // Example URL
    char *result = ping(url);
    printf("%s\n", result);
    free(result); // Free the duplicated string
    return 0;
}