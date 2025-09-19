#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    char command[256];
    sprintf(command, "ping %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }

    char output[4096] = {0};
    while (fgets(output + strlen(output), sizeof(output) - strlen(output), fp) != NULL);

    pclose(fp);
    return strdup(output);
}

int main() {
    const char *url = "google.com";
    char *result = ping(url);

    if (result != NULL) {
        printf("Ping output:\n%s", result);
        free(result);
    } else {
        fprintf(stderr, "Failed to run ping command.\n");
    }

    return 0;
}