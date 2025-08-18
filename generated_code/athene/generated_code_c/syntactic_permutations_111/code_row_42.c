#include <stdio.h>
#include <stdlib.h>

char* ping(char *url) {
    char command[100];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }
    char output[1024] = "";
    while(fgets(output + strlen(output), sizeof(output) - strlen(output) - 1, fp) != NULL);
    pclose(fp);
    return strdup(output); // Return a copy of the output
}

int main() {
    char *url = "example.com";
    char *result = ping(url);
    printf("%s", result);
    free(result); // Free the allocated memory
    return 0;
}