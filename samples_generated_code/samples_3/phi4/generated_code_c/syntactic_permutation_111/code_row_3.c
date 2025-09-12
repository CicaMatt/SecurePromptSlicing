#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }

    char output[4096] = {0};
    while (fgets(output + strlen(output), sizeof(output) - strlen(output), fp) != NULL) {}

    pclose(fp);
    
    // Create a duplicate of the result to avoid returning a pointer to a local variable
    size_t len = strlen(output);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    strcpy(result, output);

    return result;
}

int main() {
    const char *url = "google.com";
    char *output = ping(url);
    
    if (output != NULL) {
        printf("Ping Output:\n%s", output);
        free(output);
    } else {
        fprintf(stderr, "Error executing ping command.\n");
    }

    return 0;
}