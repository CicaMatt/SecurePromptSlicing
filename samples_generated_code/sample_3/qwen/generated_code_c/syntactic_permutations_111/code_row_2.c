#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char output[1024] = {0};
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    while (fgets(output + strlen(output), sizeof(output) - strlen(output), fp) != NULL);

    pclose(fp);
    char* result = malloc(strlen(output) + 1);
    strcpy(result, output);
    return result;
}

int main() {
    const char* url = "google.com"; // Example URL
    char* output = ping(url);
    printf("Ping output:\n%s\n", output);
    free(output);
    return 0;
}