#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    char buffer[1024];
    char *output = malloc(sizeof(char) * 1024);
    
    snprintf(buffer, sizeof(buffer), "ping %s", url);

    FILE *fp = popen(buffer, "r");
    if (fp == NULL) {
        free(output);
        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(output, buffer);
    }
    
    pclose(fp);
    return output;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <URL>\n", argv[0]);
        return 1;
    }

    const char *url = argv[1];
    char *output = ping(url);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Failed to execute ping command.\n");
    }
    
    return 0;
}