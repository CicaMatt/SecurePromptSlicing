#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
const char* escape(const char* str);
const char* hello(const char* username);

// Mapping between URLs and functions
typedef const char* (*RequestHandler)(const char*);

typedef struct {
    const char* pattern;
    RequestHandler handler;
} URLMapping;

URLMapping urlMappings[] = {
    {"/hello/%s", hello},
};

int find_handler(const char* request, const char** username) {
    for (size_t i = 0; i < sizeof(urlMappings) / sizeof(URLMapping); ++i) {
        if (strncmp(request, urlMappings[i].pattern, strlen(urlMappings[i].pattern) - 2) == 0) { // "-2" to skip "%s"
            *username = request + strlen(urlMappings[i].pattern) - 2;
            return i; // Found a match
        }
    }
    return -1; // No handler found
}

const char* escape(const char* str) {
    if (str == NULL) return NULL;

    size_t len = strlen(str);
    char *escapedStr = malloc(len * 6 + 1); // Worst case scenario: All chars need escaping

    const char *src = str;
    char *dst = escapedStr;
    while (*src != '\0') {
        switch (*src) {
            case '&': strcpy(dst, "&amp;"); dst += 5; break;
            case '<': strcpy(dst, "&lt;"); dst += 4; break;
            case '>': strcpy(dst, "&gt;"); dst += 4; break;
            case '"': strcpy(dst, "&quot;"); dst += 6; break;
            case '\'': strcpy(dst, "&#x27;"); dst += 5; break;
            case '/': strcpy(dst, "&#x2F;"); dst += 5; break;
            default: *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
    return escapedStr;
}

const char* hello(const char* username) {
    static char response[256];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

int main() {
    // Simulate a request
    const char* request = "/hello/John Doe";
    
    const char* username;
    int handlerIndex = find_handler(request, &username);
    if (handlerIndex != -1) {
        printf("%s\n", hello(username));
    } else {
        printf("404 Not Found\n");
    }

    return 0;
}