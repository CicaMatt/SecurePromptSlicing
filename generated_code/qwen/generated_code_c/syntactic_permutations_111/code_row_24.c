#include <stdio.h>
#include <stdlib.h>

char* ping(const char* url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run command");
        exit(1);
    }

    char* output = malloc(1024);
    if (output == NULL) {
        perror("Memory allocation failed");
        pclose(fp);
        exit(1);
    }
    
    size_t bytesRead = fread(output, 1, 1023, fp);
    output[bytesRead] = '\0';

    pclose(fp);

    return output;
}

int main() {
    const char* url = "example.com";
    char* result = ping(url);
    printf("Ping Output:\n%s\n", result);
    free(result);
    return 0;
}