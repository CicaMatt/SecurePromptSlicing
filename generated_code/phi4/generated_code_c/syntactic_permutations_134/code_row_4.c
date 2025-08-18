#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype
char* escape(const char* str);

char* hello(const char* username) {
    static char response[256];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

char* escape(const char* str) {
    if (str == NULL) return NULL;

    size_t len = strlen(str);
    char* escaped = malloc(len * 6 + 1); // Allocate enough space
    if (!escaped) return NULL;

    const char* special_chars = "&<>'\"";
    char* replacement = "&amp;<>&apos;&quot;";

    for (size_t i = 0, j = 0; i < len; ++i) {
        const char* found = strchr(special_chars, str[i]);
        if (found) {
            escaped[j++] = '%';
            escaped[j++] = '2'; // Start of hexadecimal
            escaped[j++] = "0123456789ABCDEF"[(str[i] >> 4) & 0xF];
            escaped[j++] = "0123456789ABCDEF"[str[i] & 0xF];
        } else {
            escaped[j++] = str[i];
        }
    }

    escaped[j] = '\0';
    return escaped;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* url_path = argv[1];
    
    // Simulate URL mapping
    if (strncmp(url_path, "/hello/", 7) == 0 && strlen(url_path) > 7) {
        const char* username = url_path + 7; // Skip /hello/
        printf("%s\n", hello(username));
    } else {
        fprintf(stderr, "Invalid URL\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}