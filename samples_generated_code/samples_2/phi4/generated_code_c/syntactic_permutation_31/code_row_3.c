#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
    char scheme[16];
    char netloc[256];
    char path[512];
    char params[128];
    char query[128];
    char fragment[64];
} ParsedURL;

int parse_url(const char *url, ParsedURL *parsed) {
    const char *http_pos = strstr(url, "://");
    const char *https_pos = strstr(url, "://");
    const char *start_pos;
    
    if (https_pos)
        start_pos = https_pos + 3;
    else if (http_pos)
        start_pos = http_pos + 3;
    else
        return -1;

    char *end_pos = strchr(start_pos, '/');
    strncpy(parsed->netloc, start_pos, end_pos ? end_pos - start_pos : BUFFER_SIZE);
    parsed->netloc[end_pos ? end_pos - start_pos : strlen(start_pos)] = '\0';

    if (strstr(url, "://example.com") == url) {
        return 1; // Redirect
    } else {
        return 0; // Not example.com
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    ParsedURL parsed_url = {0};
    int result = parse_url(argv[1], &parsed_url);

    if (result == 1) {
        printf("Redirecting...\n");
    } else if (result == 0) {
        printf("404 Not Found\n");
    } else {
        printf("Error parsing URL\n");
    }

    return 0;
}