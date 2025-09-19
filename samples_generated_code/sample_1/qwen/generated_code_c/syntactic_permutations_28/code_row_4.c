#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 256

const char* compile_once_module() {
    return "http://example.com/target";
}

int main() {
    const char* target_url = compile_once_module();
    const char* default_url = "http://example.com/default";
    char input_url[MAX_URL_LENGTH];

    printf("Enter the URL to match: ");
    if (fgets(input_url, MAX_URL_LENGTH, stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(input_url);
        if (len > 0 && input_url[len - 1] == '\n') {
            input_url[len - 1] = '\0';
        }

        const char* redirect_url = strcmp(input_url, target_url) == 0 ? target_url : default_url;
        printf("Redirecting to: %s\n", redirect_url);
    } else {
        printf("Failed to read URL.\n");
    }

    return 0;
}