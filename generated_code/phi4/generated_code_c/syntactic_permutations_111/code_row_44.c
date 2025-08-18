#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping %s", url);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return NULL;
    }

    char output[1024] = {0};
    size_t bytes_read = fread(output, 1, sizeof(output) - 1, fp);

    pclose(fp);

    if (bytes_read == 0) {
        return NULL;
    }
    
    return output;
}

int main() {
    const char *url = "example.com"; // Replace with the actual URL you want to ping
    char* result = ping(url);
    if (result != NULL) {
        printf("Ping Output:\n%s\n", result);
    } else {
        printf("Failed to execute ping command.\n");
    }
    return 0;
}