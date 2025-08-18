#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char cmd[100];
    sprintf(cmd, "ping -c 4 %s", url);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    char output[256];
    fgets(output, sizeof(output)-1, fp);
    pclose(fp);
    return strdup(output); // Return a copy of the output
}

int main() {
    const char* url = "example.com"; // Example URL
    char* result = ping(url);
    printf("%s\n", result);
    free(result); // Free the allocated memory
    return 0;
}