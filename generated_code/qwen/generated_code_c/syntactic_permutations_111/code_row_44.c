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

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        printf("%s", output);
    }
    pclose(fp);

    // Return a copy of the output to simulate returning it from the function
    char *result = malloc(strlen(output) + 1);
    if (result == NULL) {
        perror("malloc() failed.");
        exit(EXIT_FAILURE);
    }
    strcpy(result, output);

    return result;
}

int main() {
    const char* url = "example.com";
    char* output = ping(url);
    printf("Ping output: %s", output);
    free(output);
    return 0;
}