#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *str) {
    int len = strlen(str);
    char *escaped_str = (char *)malloc(3 * len + 1); // Each character could be up to 3 chars in escaped form
    int j = 0;
    for (int i = 0; i < len; i++) {
        switch (str[i]) {
            case '&': 
                strcpy(&escaped_str[j], "&amp;");
                j += 5;
                break;
            case '<': 
                strcpy(&escaped_str[j], "&lt;");
                j += 4;
                break;
            case '>': 
                strcpy(&escaped_str[j], "&gt;");
                j += 4;
                break;
            case '"': 
                strcpy(&escaped_str[j], "&quot;");
                j += 6;
                break;
            case '\'': 
                strcpy(&escaped_str[j], "&#39;");
                j += 5;
                break;
            default:
                escaped_str[j++] = str[i];
        }
    }
    escaped_str[j] = '\0';
    return escaped_str;
}

void hello(const char *username) {
    char *safe_username = escape(username);
    printf("Hello %s\n", safe_username);
    free(safe_username);
}

int main() {
    // Simulating navigation to /hello/username
    const char *url = "/hello/example_user";
    const char *username = url + 7; // Extracting username from URL
    hello(username);
    return 0;
}