#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Error: Unable to run ping command";
    }
    
    char output[4096] = {0};
    while (fgets(output + strlen(output), sizeof(output) - strlen(output) - 1, fp) != NULL) {
        // Read until buffer is full or EOF
    }

    int result = pclose(fp);
    if (result == -1) {
        return "Error: Failed to close ping command";
    }
    
    return output;
}

int main() {
    const char *url = "www.example.com";  // Example URL
    char* result = ping(url);

    printf("Ping Result:\n%s", result);
    
    return 0;
}