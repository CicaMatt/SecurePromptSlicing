#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    static char output[1024];
    snprintf(output, sizeof(output), "ping %s", url);
    FILE *fp = popen(output, "r");
    if (fp == NULL) {
        return "Error executing ping command";
    }
    
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strncat(output, buffer, sizeof(output) - strlen(output) - 1);
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
    char *result = ping(url);
    printf("%s\n", result);

    return 0;
}