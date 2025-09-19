#include <stdio.h>
#include <stdlib.h>

char* ping(const char *url) {
    static char output[1024];
    char command[512];

    snprintf(command, sizeof(command), "ping %s", url);
    FILE *fp = popen(command, "r");
    
    if (fp == NULL) {
        return "Error: Unable to run ping command.";
    }

    size_t bytes_read = fread(output, 1, sizeof(output) - 1, fp);
    output[bytes_read] = '\0';

    pclose(fp);

    return output;
}

int main() {
    const char *url = "www.google.com";
    printf("Pinging %s:\n", url);
    char *result = ping(url);
    printf("%s\n", result);
    return 0;
}