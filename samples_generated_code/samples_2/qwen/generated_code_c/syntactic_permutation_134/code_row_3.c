#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 1024
#define MAX_RESPONSE_LENGTH 1024

char *escape(const char *input) {
    int i, j;
    int len = strlen(input);
    char *output = (char *)malloc(len * 6 + 1); // Maximum length if all chars are escaped
    for (i = 0, j = 0; i < len; i++) {
        switch (input[i]) {
            case '<': strcpy(&output[j], "&lt;"); j += 4; break;
            case '>': strcpy(&output[j], "&gt;"); j += 4; break;
            case '&': strcpy(&output[j], "&amp;"); j += 5; break;
            case '"': strcpy(&output[j], "&quot;"); j += 6; break;
            case '\'': strcpy(&output[j], "&#39;"); j += 5; break;
            default: output[j++] = input[i]; break;
        }
    }
    output[j] = '\0';
    return output;
}

char *hello(const char *username) {
    char *escaped_username = escape(username);
    char *response = (char *)malloc(MAX_RESPONSE_LENGTH);
    snprintf(response, MAX_RESPONSE_LENGTH, "Hello %s", escaped_username);
    free(escaped_username);
    return response;
}

void route_handler(const char *url) {
    char username[MAX_URL_LENGTH];
    if (sscanf(url, "/hello/%1023s", username) == 1) {
        char *response = hello(username);
        printf("%s\n", response);
        free(response);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *url = "/hello/user&name";
    route_handler(url);
    return 0;
}