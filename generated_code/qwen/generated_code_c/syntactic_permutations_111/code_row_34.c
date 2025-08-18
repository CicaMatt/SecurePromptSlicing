#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char output[1024];

    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        printf("%s", output);
    }

    pclose(fp);

    return strdup(output); // Note: The caller must free this memory
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <URL>\n", argv[0]);
        exit(1);
    }

    const char* url = argv[1];
    char* result = ping(url);

    printf("Ping output: %s\n", result);

    free(result); // Free the memory allocated by strdup

    return 0;
}