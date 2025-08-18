#include <stdio.h>
#include <string.h>

#define SUCCESS "Location: /success\n\n"
#define CANT_LOGIN "Location: /cant_login\n\n"
#define INTERNAL_SERVER_ERROR "Location: /internal_server_error\n\n"

int authenticate(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "123456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1;
    }
    return 0;
}

int main() {
    char username[100];
    char password[100];

    printf("Content-Type: text/html\n");

    // Simulate reading from a POST request
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0) {
            fread(username, sizeof(char), 100, stdin);
            fread(password, sizeof(char), 100, stdin);

            // Parse form data
            char *separator = strchr(username, '&');
            if (separator != NULL) {
                *separator = '\0';
                strcpy(password, separator + 1);
                password[strcspn(password, "=")] = '\0';
                username[strcspn(username, "=")] = '\0';

                // Remove leading "username=" and "password="
                username += 9;
                password += 9;

                if (authenticate(username, password)) {
                    printf(SUCCESS);
                } else {
                    printf(CANT_LOGIN);
                }
            } else {
                printf(INTERNAL_SERVER_ERROR);
            }
        } else {
            printf(INTERNAL_SERVER_ERROR);
        }
    } else {
        printf(INTERNAL_SERVER_ERROR);
    }

    return 0;
}