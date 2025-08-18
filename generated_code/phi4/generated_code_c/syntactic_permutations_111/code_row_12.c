#include <stdio.h>
#include <stdlib.h>

char* get_url_from_request(const char *request) {
    // This is just a placeholder for extracting URL from the request.
    // In practice, you'd parse the HTTP request to find the URL.
    return "example.com"; 
}

char* ping(char *url) {
    char command[256];
    snprintf(command, sizeof(command), "ping -c 4 %s", url);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        return NULL;
    }

    static char output[10240]; // Static to ensure it persists after function call
    char buffer[512];
    size_t total_length = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        strncat(output + total_length, buffer, sizeof(output) - total_length - 1);
        total_length += strlen(buffer);
    }

    pclose(fp);

    return output;
}

int main() {
    const char *request = "GET / HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n";
    char *url = get_url_from_request(request);
    
    if (url) {
        char *output = ping(url);
        if (output) {
            printf("Ping Output:\n%s", output);
        }
    }

    return 0;
}