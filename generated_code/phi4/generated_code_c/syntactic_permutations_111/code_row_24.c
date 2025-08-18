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
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strcat(output, buffer);
    }
    
    int result = pclose(fp);
    if (result == -1) {
        return "Failed to close process";
    }
    
    return output;
}

int main() {
    const char *url = "google.com";  // Example URL
    printf("Ping Output:\n%s\n", ping(url));
    return 0;
}