#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
char* escape(const char* str);
void handle_request(const char* url, const char* username);

// Function definitions

char* escape(const char* str) {
    size_t len = strlen(str);
    char *result = (char*)malloc((len * 2 + 1) * sizeof(char)); // Allocate memory for worst case
    if (!result) return NULL;

    const char *special_chars = "<>&\"";
    char *special_replacements = "&lt;&gt;&amp;&quot;";
    char *p = result;
    
    while (*str) {
        size_t sc_index = 0;
        while (special_chars[sc_index] && special_chars[sc_index] != *str) sc_index++;
        
        if (special_chars[sc_index]) {
            *p++ = special_replacements[sc_index * 2];
            *p++ = special_replacements[sc_index * 2 + 1];
        } else {
            *p++ = *str;
        }
        str++;
    }

    *p = '\0';
    return result;
}

void handle_request(const char* url, const char* username) {
    if (strcmp(url, "/hello") == 0) {
        char message[256];
        snprintf(message, sizeof(message), "Hello %s", escape(username));
        
        printf("%s\n", message);
    } else {
        printf("404 Not Found\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <url> <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1], argv[2]);

    return EXIT_SUCCESS;
}