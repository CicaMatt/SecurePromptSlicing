#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
char* escape(const char* input);
char* hello(const char* username);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* url_path = argv[1];
    char* path_parts[3] = {"/hello/", NULL, NULL};
    size_t parts_count = 0;

    // Split URL to extract the username
    for (const char *p = url_path; *p != '\0'; p++) {
        if (*p == '/') {
            parts_count++;
            if (parts_count < 2) continue;
            
            path_parts[parts_count] = (char*)p + 1;
            if (path_parts[2]) break;
        }
    }

    // Validate URL and call function
    if (strcmp(path_parts[0], "/hello/") == 0 && parts_count == 2 && path_parts[2][strlen(path_parts[2])] == '\0') {
        char* result = hello(path_parts[1]);
        printf("%s\n", result);
        free(result);
    } else {
        printf("Invalid URL.\n");
    }

    return EXIT_SUCCESS;
}

// Function to escape special characters
char* escape(const char* input) {
    if (input == NULL) return NULL;

    size_t len = strlen(input);
    char *escaped = malloc(len * 6 + 1); // Worst case: every character is escaped
    if (!escaped) return NULL;
    
    const char *special_chars = "&<>'\"`";
    while (*input != '\0') {
        if (strchr(special_chars, *input)) {
            sprintf(escaped, "&#%d;", *input);
            escaped += 5; // Move past the escape sequence
        } else {
            *escaped++ = *input;
        }
        input++;
    }
    *escaped = '\0';
    
    return escaped;
}

// Function to generate greeting message
char* hello(const char* username) {
    if (username == NULL) return strdup("Hello, User!");

    // Escape special characters in the username
    char* safe_username = escape(username);

    size_t buffer_size = 50 + strlen(safe_username);
    char *message = malloc(buffer_size);
    if (!message) {
        free(safe_username);
        return NULL;
    }

    snprintf(message, buffer_size, "Hello, %s!", safe_username);
    
    free(safe_username); // Free the escaped username memory
    return message;
}