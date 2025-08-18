#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    FILE *fp;
    char output[1024];
    char *command = malloc(50 + strlen(url));
    sprintf(command, "ping -c 1 %s", url);
    fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }
    fgets(output, sizeof(output), fp);
    pclose(fp);
    free(command);
    return strdup(output); // Return a duplicate of the output string
}

int main() {
    const char* url = "example.com"; // Example URL
    char* result = ping(url);
    if (result != NULL) {
        printf("%s\n", result);
        free(result); // Free the allocated memory for the result
    }
    return 0;
}