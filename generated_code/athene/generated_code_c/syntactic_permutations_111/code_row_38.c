#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define BUFFER_SIZE 4096

char* ping(const char *url) {
    static char output[BUFFER_SIZE];
    char command[BUFFER_SIZE];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return "Failed to run ping command";
    }
    fgets(output, sizeof(output), fp);
    pclose(fp);
    return output;
}

int main() {
    const char *url = "example.com"; // Example URL
    char *result = ping(url);
    printf("%s", result);
    return 0;
}