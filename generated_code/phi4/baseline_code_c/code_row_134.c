#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char* str) {
    static char escaped[256];
    const char *p;
    char *q = escaped;
    
    for (p = str; *p != '\0'; p++) {
        switch (*p) {
            case '&': strcpy(q, "&amp;"); q += 5; break;
            case '<': strcpy(q, "&lt;"); q += 4; break;
            case '>': strcpy(q, "&gt;"); q += 4; break;
            case '"': strcpy(q, "&quot;"); q += 6; break;
            default: *q++ = *p;
        }
    }
    *q = '\0';
    
    return escaped;
}

char* hello(const char* username) {
    static char response[256];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

void handle_request(const char* url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char *username = url + 7;
        printf("%s\n", hello(username));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Example usage:
    handle_request("/hello/John Doe"); // Should print: Hello John&amp;nbsp;Doe
    return 0;
}