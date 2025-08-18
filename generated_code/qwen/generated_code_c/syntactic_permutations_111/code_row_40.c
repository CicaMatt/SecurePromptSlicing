#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char result[1024] = {0};
    fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run command";
    }

    while (fgets(result, sizeof(result)-1, fp) != NULL) {
        // Accumulate results
    }
    pclose(fp);

    char *output = malloc(strlen(result) + 1);
    if (output == NULL) {
        return "Memory allocation failed";
    }
    strcpy(output, result);
    return output;
}

int main() {
    const char* url = "google.com"; // Example URL
    char* response = ping(url);
    printf("Ping Response:\n%s", response);
    free(response);
    return 0;
}