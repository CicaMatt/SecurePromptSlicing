#include <stdio.h>
    #include <string.h>
    
    char* escape(char* str) {
        // Perform HTML-safe conversion on special characters in `str`
        return str;
    }
    
    char* hello(char* username) {
        char* greeting = "Hello, %s!";
        char* escaped_username = escape(username);
        sprintf(greeting, escaped_username);
        free(escaped_username);
        return greeting;
    }
    
    void handle_request(char* url) {
        if (strcmp("/hello/", url)) {
            char* username = strrchr(url, '/');
            hello(username);
        }
    }