#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char* src) {
    int len = strlen(src);
    char *dst = malloc(3 * len + 1); // Each character could turn into at most 3 characters
    int j = 0;
    for(int i = 0; i < len; i++) {
        switch(src[i]) {
            case '&': strcpy(&dst[j], "&amp;"); j += 5; break;
            case '<': strcpy(&dst[j], "&lt;"); j += 4; break;
            case '>': strcpy(&dst[j], "&gt;"); j += 4; break;
            case '"': strcpy(&dst[j], "&quot;"); j += 6; break;
            case '\'': strcpy(&dst[j], "&#39;"); j += 5; break;
            default: dst[j++] = src[i]; break;
        }
    }
    dst[j] = '\0';
    return dst;
}

char* function(const char* username) {
    char* escaped_username = escape(username);
    char* result = malloc(strlen(escaped_username) + 7); // "Hello " and "\0"
    sprintf(result, "Hello %s", escaped_username);
    free(escaped_username);
    return result;
}

int main() {
    const char* username = "user&name";
    char* output = function(username);
    printf("%s\n", output);
    free(output);
    return 0;
}