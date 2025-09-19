#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "correct_user"
#define PASSWORD "correct_pass"

void handle_request(const char *url) {
    const char *username = NULL;
    const char *password = NULL;

    if (strncmp(url, "/check_mod?user=", 16) == 0) {
        username = url + 16;
        const char *start = strchr(username, '&');
        if (start != NULL) {
            password = start + 1;
            *(char*)start = '\0';
        }
    }

    if ((username != NULL && strcmp(USERNAME, username) == 0) &&
        (password != NULL && strcmp(PASSWORD, password) == 0)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

int main() {
    char input[256];

    printf("Enter the URL: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[--len] = '\0'; // Remove newline character
        }
        handle_request(input);
    }

    return 0;
}