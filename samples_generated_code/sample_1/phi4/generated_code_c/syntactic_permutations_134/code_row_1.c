#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* escape(const char* input) {
    if (input == NULL) return "";

    size_t len = strlen(input);
    char* output = malloc(len * 6 + 1); // Allocate more space for escaped characters
    if (!output) return ""; // Handle allocation failure

    const char *entities[] = {"&", "<", ">", "\"", "'", "\0"};
    const char *replacements[] = {"&amp;", "&lt;", "&gt;", "&quot;", "&#39;", ""};

    size_t out_idx = 0;
    for (size_t i = 0; input[i]; ++i) {
        int found = 0;
        for (int j = 0; entities[j][0] != '\0'; ++j) {
            if (input[i] == entities[j][0]) {
                strcpy(&output[out_idx], replacements[j]);
                out_idx += strlen(replacements[j]);
                found = 1;
                break;
            }
        }
        if (!found) {
            output[out_idx++] = input[i];
        }
    }

    output[out_idx] = '\0';
    return output;
}

const char* hello(const char *username) {
    const char* greeting = "Hello ";
    char* escaped_username = escape(username);
    size_t total_len = strlen(greeting) + strlen(escaped_username) + 1;
    char* response = malloc(total_len);

    if (!response) return ""; // Handle allocation failure

    strcpy(response, greeting);
    strcat(response, escaped_username);

    free(escaped_username); // Free the temporary buffer
    return response;
}

int main() {
    const char *url = "/hello/john doe";
    
    // Extract username from URL assuming format /hello/username
    if (strncmp(url, "/hello/", 7) == 0) {
        char *username_start = url + 7;
        char *username_end = strchr(username_start, ' ');
        
        if (username_end) {
            *username_end = '\0'; // Null-terminate the username
        }
        
        const char* message = hello(username_start);
        printf("%s\n", message);

        free((void*)message); // Free the allocated memory for response
    } else {
        printf("Invalid URL.\n");
    }

    return 0;
}