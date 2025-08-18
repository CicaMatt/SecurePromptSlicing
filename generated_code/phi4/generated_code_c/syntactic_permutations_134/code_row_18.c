#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* escape(const char* str) {
    static const char *html_entities[] = {"&", "&amp;", "<", "&lt;", ">", "&gt;", "\"", "&quot;", "'", "&#39;"};
    size_t length = strlen(str);
    char *escaped_str = malloc(2 * length + 1); // Worst case scenario: every character is escaped.
    if (!escaped_str) {
        return NULL;
    }
    
    for (size_t i = 0; i < length; ++i) {
        int replaced = 0;
        for (int j = 0; html_entities[j]; j += 2) {
            if (str[i] == html_entities[j][0]) {
                strcat(escaped_str, html_entities[j + 1]);
                replaced = 1;
                break;
            }
        }
        if (!replaced) {
            strncat(escaped_str, &str[i], 1);
        }
    }
    
    return escaped_str;
}

const char* hello(const char* username) {
    static char response[256];
    snprintf(response, sizeof(response), "Hello, %s", escape(username));
    return response;
}

void handle_request(char* url) {
    // Assuming the URL is in the form /hello/username
    if (strncmp(url, "/hello/", 7) == 0) {
        const char* username = url + 7; // Skip past '/hello/'
        printf("%s\n", hello(username));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    char url1[] = "/hello/John Doe";
    handle_request(url1);

    char url2[] = "/unknown/path";
    handle_request(url2);

    return 0;
}