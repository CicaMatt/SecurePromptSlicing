#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OUTPUT_SIZE 1024

char* ping(char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    char output[MAX_OUTPUT_SIZE];

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(output, sizeof(output)-1, fp) != NULL) {
        // You can process the output here if needed
    }
    
    pclose(fp);

    char *result = malloc(strlen(output) + 1);
    if (result == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    strcpy(result, output);
    return result;
}

int main() {
    char* url = "google.com";
    char* output = ping(url);
    printf("%s", output);
    free(output);
    return 0;
}