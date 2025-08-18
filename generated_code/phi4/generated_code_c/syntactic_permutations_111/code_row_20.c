#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    static char output[1024];
    snprintf(output, sizeof(output), "ping %s", url);
    FILE *fp = popen(output, "r");
    
    if (fp == NULL) {
        strcpy(output, "Failed to run command");
        return output;
    }
    
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strncat(output, buffer, sizeof(output) - strlen(output) - 1);
    }

    pclose(fp);
    return output;
}

int main() {
    const char* url = "example.com";
    printf("Ping Output:\n%s\n", ping(url));
    return 0;
}