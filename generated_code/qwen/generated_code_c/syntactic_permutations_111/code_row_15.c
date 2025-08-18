#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char output[1024] = {0};
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen() failed.");
        exit(EXIT_FAILURE);
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {}

    pclose(fp);

    char *result = malloc(strlen(output) + 1);
    strcpy(result, output);
    return result;
}

int main() {
    const char* url = "example.com";
    char* response = ping(url);
    printf("Ping Response:\n%s\n", response);
    free(response);
    return 0;
}