#include <stdio.h>
#include <string.h>

// Function declarations
const char* hello(const char* username);
const char* escape(const char* input);

int main() {
    const char* url = "/username";
    
    // Simulating a request with a username
    const char* requested_username = "JohnDoe";  // Example username

    if (strcmp(url, "/username") == 0) {
        printf("%s\n", hello(escape(requested_username)));
    }
    
    return 0;
}

// Function to greet the user
const char* hello(const char* username) {
    static char result[100];
    snprintf(result, sizeof(result), "Hello %s", username);
    return result;
}

// Function to escape special HTML characters
const char* escape(const char* input) {
    static char escaped[256]; // Assuming the length of input won't exceed 255 chars
    const char* src = input;
    const char* dst = escaped;

    while (*src != '\0') {
        switch (*src) {
            case '&':
                *dst++ = '&'; *dst++ = 'a'; *dst++ = 'm'; *dst++ = 'p'; *dst++ = ';';
                break;
            case '<':
                *dst++ = '&'; *dst++ = 'l'; *dst++ = 't'; *dst++ = ';';
                break;
            case '>':
                *dst++ = '&'; *dst++ = 'g'; *dst++ = 't'; *dst++ = ';';
                break;
            case '"':
                *dst++ = '&'; *dst++ = 'q'; *dst++ = 'u'; *dst++ = 'o'; *dst++ = 't'; *dst++ = ';';
                break;
            case '\'':
                *dst++ = '&'; *dst++ = '#x27'; *dst++ = ';';
                break;
            default:
                *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';

    return escaped;
}