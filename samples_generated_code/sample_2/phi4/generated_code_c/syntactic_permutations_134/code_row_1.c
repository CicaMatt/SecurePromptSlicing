#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

char* escape(const char* input) {
    static char output[1024];
    const char* safe_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    size_t i, j;
    
    for (i = 0, j = 0; input[i] != '\0'; ++i) {
        if (strchr(safe_chars, input[i])) {
            output[j++] = input[i];
        } else {
            snprintf(&output[j], sizeof(output) - j, "&%02x;", (unsigned char)input[i]);
            j += 4;
        }
    }

    output[j] = '\0';
    return output;
}

char* hello(const char* username) {
    static char greeting[256];
    snprintf(greeting, sizeof(greeting), "Hello %s", escape(username));
    return greeting;
}

void handle_request(const char* url) {
    char *username_start, *username_end;

    if (strncmp(url, "/hello/", 7) == 0) {
        username_start = url + 7;
        username_end = strchr(username_start, '/');
        
        if (!username_end) {
            printf("Invalid URL format.\n");
            return;
        }
        
        *username_end = '\0'; // Temporarily terminate the string for processing
        
        char* response = hello(username_start);
        printf("%s\n", response);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    char url[MAX_URL_LENGTH];
    
    printf("Enter URL: ");
    if (fgets(url, sizeof(url), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(url);
        if (len > 0 && url[len - 1] == '\n') {
            url[--len] = '\0';
        }
        
        handle_request(url);
    }

    return 0;
}