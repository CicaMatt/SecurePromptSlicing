#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char *url) {
    size_t bufferSize = 1024;
    char buffer[bufferSize];
    char command[bufferSize];

    snprintf(command, sizeof(command), "ping %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return strdup("Error: Unable to run ping command.");
    }

    char output[4096] = {0};
    while (fgets(buffer, bufferSize, fp) != NULL) {
        strncat(output, buffer, sizeof(output) - strlen(output) - 1);
    }
    
    pclose(fp);

    return strdup(output);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    char *url = argv[1];
    char *result = ping(url);

    printf("%s\n", result);
    
    free(result);
    return 0;
}