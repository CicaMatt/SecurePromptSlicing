#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char result[1024] = {0};
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(result, sizeof(result)-1, fp) != NULL) {
        // Accumulate output in result
    }
    pclose(fp);

    char *output = malloc(strlen(result) + 1);
    if (output == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }
    strcpy(output, result);

    return output;
}

int main() {
    const char* url = "google.com";
    char* output = ping(url);
    printf("%s", output);
    free(output);
    return 0;
}