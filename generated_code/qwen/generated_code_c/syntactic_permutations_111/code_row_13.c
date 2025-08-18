#include <stdio.h>
#include <stdlib.h>

char* ping(char* url) {
    char command[50];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }

    char* output = malloc(128 * sizeof(char));
    if (output == NULL) {
        pclose(fp);
        return "Memory allocation failed";
    }
    
    while (fgets(output, 128, fp) != NULL) {}

    pclose(fp);
    return output;
}

int main() {
    char* url = "google.com";
    char* result = ping(url);
    printf("%s\n", result);
    free(result);
    return 0;
}