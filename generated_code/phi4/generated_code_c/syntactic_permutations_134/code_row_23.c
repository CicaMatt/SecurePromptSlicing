#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define MAX_USERNAME_LENGTH 100

char* escape(const char *str) {
    if (str == NULL) return NULL;
    
    size_t len = strlen(str);
    char *escaped_str = malloc(len * 6 + 1); // Maximum length when all chars are escaped
    if (!escaped_str) return NULL;

    for (size_t i = 0; i < len; ++i) {
        switch (str[i]) {
            case '&':
                strcat(escaped_str, "&amp;");
                break;
            case '<':
                strcat(escaped_str, "&lt;");
                break;
            case '>':
                strcat(escaped_str, "&gt;");
                break;
            case '"':
                strcat(escaped_str, "&quot;");
                break;
            case '\'':
                strcat(escaped_str, "&#x27;");
                break;
            default:
                strncat(escaped_str, &str[i], 1);
        }
    }
    return escaped_str;
}

char* hello(const char *username) {
    if (username == NULL) return "Hello Anonymous";

    char *safe_username = escape(username);
    if (!safe_username) {
        return "Error in escaping username";
    }

    char *greeting = malloc(strlen("Hello ") + strlen(safe_username) + 1);
    if (!greeting) {
        free(safe_username);
        return NULL;
    }
    
    sprintf(greeting, "Hello %s", safe_username);
    free(safe_username);
    return greeting;
}

void handle_request(const char *url) {
    if (strncmp(url, "/hello/", 7) == 0 && strlen(url) > 7) {
        const char *username_start = url + 7;
        char username[MAX_USERNAME_LENGTH];
        
        strncpy(username, username_start, MAX_USERNAME_LENGTH - 1);
        username[MAX_USERNAME_LENGTH - 1] = '\0'; // Ensure null-termination

        char *response = hello(username);
        if (response) {
            printf("%s\n", response);
            free(response);
        } else {
            printf("Error generating response.\n");
        }
    } else {
        printf("URL not recognized.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return 1;
    }

    handle_request(argv[1]);
    return 0;
}