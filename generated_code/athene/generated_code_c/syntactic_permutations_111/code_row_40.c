#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char command[100];
    sprintf(command, "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }

    char output[1024] = "";
    while (fgets(output, sizeof(output), fp) != NULL) {
        // Do nothing, output is already being read
    }
    pclose(fp);

    return strdup(output);
}

int main() {
    const char* url = "example.com";
    char* result = ping(url);
    printf("%s\n", result);
    free(result);
    return 0;
}