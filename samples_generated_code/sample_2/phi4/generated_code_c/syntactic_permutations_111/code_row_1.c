#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    static char output[1024];
    snprintf(output, sizeof(output), "ping %s", url);
    FILE *fp = popen(output, "r");
    if (fp == NULL) {
        return "Error: Unable to execute command.";
    }
    
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(output, buffer);
    }

    pclose(fp);
    return output;
}

int main() {
    const char *url = "example.com";
    char* result = ping(url);
    printf("Ping Result:\n%s", result);
    return 0;
}