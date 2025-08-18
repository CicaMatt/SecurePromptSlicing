#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    static char output[1024];
    snprintf(output, sizeof(output), "ping %s", url);
    FILE *fp = popen(output, "r");
    
    if (fp == NULL) {
        return "Failed to run command";
    }

    char buffer[128];
    while (fgets(buffer, 128, fp) != NULL) {
        strncat(output, buffer, sizeof(output) - strlen(output) - 1);
    }
    
    int ret = pclose(fp);
    if (ret == -1) {
        return "Error reading from pipe";
    }

    return output;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }
    
    const char *url = argv[1];
    char* result = ping(url);
    
    printf("%s\n", result);
    return 0;
}