#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    static char buffer[1024];
    const char *special_chars = "&<>'\"`";
    char *safe_str = buffer;
    
    while (*str) {
        if (strchr(special_chars, *str)) {
            switch (*str) {
                case '&': strcpy(safe_str, "&amp;"); break;
                case '<': strcpy(safe_str, "&lt;"); break;
                case '>': strcpy(safe_str, "&gt;"); break;
                case '\'': strcpy(safe_str, "&#39;"); break;
                case '"': strcpy(safe_str, "&quot;"); break;
                case '`': strcpy(safe_str, "&#96;"); break;
            }
            str++;
            safe_str += strlen(buffer);
        } else {
            *safe_str++ = *str++;
        }
    }
    
    *safe_str = '\0';
    return buffer;
}

char* hello(const char *username) {
    static char response[256];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

int main() {
    const char *url = "/hello/JohnDoe";
    
    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username = url + 7;
        
        // Simulating URL parsing and function calling
        printf("%s\n", hello(username));
    }
    
    return 0;
}