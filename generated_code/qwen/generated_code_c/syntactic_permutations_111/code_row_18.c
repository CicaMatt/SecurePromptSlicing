#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char output[1035];

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Process the output as needed
    }

    pclose(fp);

    char* result = malloc(strlen(output) + 1);
    if (result == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(result, output);

    return result;
}

int main() {
    const char* url = "example.com";
    char* response = ping(url);
    printf("%s", response);
    free(response);
    return 0;
}