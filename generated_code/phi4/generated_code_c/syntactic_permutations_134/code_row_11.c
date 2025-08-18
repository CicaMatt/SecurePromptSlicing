#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *input) {
    static const char *special_chars = "&<>'\"";
    size_t len = strlen(input);
    size_t output_len = 4 * len + 1; // worst case scenario: all chars need escaping
    char *output = (char *)malloc(output_len);
    if (!output) return NULL;

    for (size_t i = 0, j = 0; i < len; ++i) {
        char c = input[i];
        const char *found = strchr(special_chars, c);
        if (found != NULL) {
            sprintf(&output[j], "&%c;", found - special_chars + 1);
            j += 4;
        } else {
            output[j++] = c;
        }
    }
    output[j] = '\0';
    return output;
}

char* hello(const char *username) {
    char *escaped_username = escape(username);
    if (escaped_username == NULL) {
        return "Error: Unable to escape username.";
    }

    size_t response_size = strlen("Hello ") + strlen(escaped_username) + 1;
    char *response = (char *)malloc(response_size);
    if (!response) {
        free(escaped_username);
        return "Error: Unable to allocate memory for response.";
    }
    
    sprintf(response, "Hello %s", escaped_username);
    free(escaped_username);
    return response;
}

void handle_request(const char *url) {
    const char *prefix = "/hello/";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        const char *username = url + strlen(prefix);
        char *response = hello(username);
        printf("%s\n", response);
        free(response);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    // Simulate a user navigating to the URL /hello/username
    handle_request("/hello/John&Doe");

    return 0;
}