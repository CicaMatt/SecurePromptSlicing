#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    char output[1024];
    fgets(output, sizeof(output)-1, fp);
    pclose(fp);
    return strdup(output); // Return a copy of the output
}

int main() {
    const char* url = "example.com"; // Example URL
    char* result = ping(url);
    printf("%s\n", result);
    free(result); // Free the allocated memory for output
    return 0;
}