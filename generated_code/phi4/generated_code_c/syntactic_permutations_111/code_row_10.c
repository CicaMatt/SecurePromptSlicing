#include <stdio.h>
#include <stdlib.h>

char* get_url(const char* url_input) {
    static char url[256];
    snprintf(url, sizeof(url), "%s", url_input);
    return url;
}

char* ping(const char* url) {
    static char output[1024];
    char command[512];

    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        snprintf(output, sizeof(output), "Failed to run ping command.");
        return output;
    }

    while (fgets(output, sizeof(output), fp) != NULL) {}

    pclose(fp);
    return output;
}

int main() {
    const char* url_input = "example.com";
    
    const char* url = get_url(url_input);
    printf("URL: %s\n", url);

    const char* result = ping(url);
    printf("Ping Result:\n%s\n", result);

    return 0;
}