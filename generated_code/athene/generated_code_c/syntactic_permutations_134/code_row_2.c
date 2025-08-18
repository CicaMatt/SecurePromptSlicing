#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void escape(char *input, char *output) {
    for (int i = 0, j = 0; input[i] != '\0'; i++) {
        switch (input[i]) {
            case '<': 
                strcpy(&output[j], "&lt;");
                j += 4;
                break;
            case '>': 
                strcpy(&output[j], "&gt;");
                j += 4;
                break;
            case '&': 
                strcpy(&output[j], "&amp;");
                j += 5;
                break;
            case '"': 
                strcpy(&output[j], "&quot;");
                j += 6;
                break;
            case '\'':
                strcpy(&output[j], "&#39;");
                j += 5;
                break;
            default:
                output[j] = input[i];
                j++;
        }
    }
    output[strlen(output)] = '\0';
}

char* hello(char *username) {
    static char response[200];
    char escaped_username[MAX_USERNAME_LENGTH * 6]; // Considering the longest escape sequence
    escape(username, escaped_username);
    snprintf(response, sizeof(response), "Hello %s", escaped_username);
    return response;
}

void route_to_function(const char *url, const char *path_info, char *username) {
    if (strcmp(url, path_info) == 0) {
        printf("%s\n", hello(username));
    }
}

int main() {
    const char *url = "/hello/username";
    const char *path_info = "/hello/";
    char username[] = "John Doe";
    route_to_function(url, path_info, username);
    return 0;
}