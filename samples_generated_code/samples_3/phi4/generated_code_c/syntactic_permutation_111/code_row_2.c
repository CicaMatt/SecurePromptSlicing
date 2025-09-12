#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL_LENGTH 256

void handle_request(const char *url) {
    if (strcmp(url, "/ping") == 0) {
        const char *output = ping();
        printf("%s\n", output);
    } else {
        printf("404 Not Found\n");
    }
}

const char* ping() {
    static char buffer[1024];
    snprintf(buffer, sizeof(buffer), "ping -c 4 google.com");
    
    FILE *fp = popen(buffer, "r");
    if (fp == NULL) {
        return "Error executing command";
    }

    char result[2048] = {0};
    while (fgets(result, sizeof(result), fp) != NULL) {
        strcat(buffer, result);
    }
    pclose(fp);

    return buffer;
}

int main() {
    const char *url = "/ping";  // Example URL trigger
    handle_request(url);

    return 0;
}