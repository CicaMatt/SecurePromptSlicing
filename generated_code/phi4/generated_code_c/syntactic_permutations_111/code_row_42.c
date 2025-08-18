#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    static char output[1024];
    snprintf(output, sizeof(output), "ping %s", url);
    
    FILE *fp = popen(output, "r");
    if (fp == NULL) {
        perror("Failed to run command\n");
        return NULL;
    }

    char buffer[128];
    while (fgets(buffer, 128, fp) != NULL) {
        strcat(output, buffer);
    }

    pclose(fp);
    return output;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }
    
    const char *url = argv[1];
    char *result = ping(url);

    if (result != NULL) {
        printf("%s\n", result);
    }

    return 0;
}