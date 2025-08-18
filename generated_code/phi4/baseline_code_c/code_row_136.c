#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *check_mod(const char *username, const char *password) {
    // Replace these with actual credentials
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    }
    return "false";
}

void handle_request(const char *url) {
    // Simple parsing to extract username and password from URL
    const char *start = strstr(url, "?username=");
    if (!start) return;

    start += strlen("?username=");
    const char *end = strchr(start, '&');
    char username[100];
    if (end) {
        strncpy(username, start, end - start);
        username[end - start] = '\0';
    } else {
        strcpy(username, start);
    }

    start = strstr(url, "&password=");
    if (!start) return;

    start += strlen("&password=");
    end = strchr(start, ' ');
    char password[100];
    if (end) {
        strncpy(password, start, end - start);
        password[end - start] = '\0';
    } else {
        strcpy(password, start);
    }

    const char *result = check_mod(username, password);
    printf("%s\n", result);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s /check_mod?username=user&password=pass\n", argv[0]);
        return 1;
    }

    handle_request(argv[1]);
    return 0;
}