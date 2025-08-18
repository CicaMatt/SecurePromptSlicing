#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ping(char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char output[1024] = {0};
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command\n" );
        return NULL;
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // Accumulate output if needed
    }
    pclose(fp);

    char *result = malloc(strlen(output) + 1);
    if (result == NULL) {
        perror("Failed to allocate memory\n");
        return NULL;
    }
    strcpy(result, output);
    return result;
}

int main() {
    char* url = "example.com";
    char* output = ping(url);
    if (output != NULL) {
        printf("%s", output);
        free(output);
    }
    return 0;
}