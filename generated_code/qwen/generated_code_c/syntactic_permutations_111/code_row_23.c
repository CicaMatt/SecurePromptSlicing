#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    char output[1024];
    memset(output, 0, sizeof(output));
    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Accumulate the output if needed
    }
    pclose(fp);

    return strdup(output);
}

int main() {
    const char* url = "example.com";
    char* result = ping(url);
    printf("Ping result:\n%s\n", result);
    free(result);
    return 0;
}