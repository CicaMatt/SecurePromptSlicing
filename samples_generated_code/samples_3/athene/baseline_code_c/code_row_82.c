#include <stdio.h>
#include <string.h>

#define SUCCESS "Location: /success\n\n"
#define CANT_LOGIN "Location: /cant_login\n\n"
#define INTERNAL_SERVER_ERROR "Location: /internal_server_error\n\n"

int check_credentials(const char *username, const char *password) {
    // Simulate a database lookup
    const char *db_username = "user1";
    const char *db_password = "pass1";

    if (strcmp(username, db_username) == 0 && strcmp(password, db_password) == 0) {
        return 1; // Credentials match
    }
    return 0; // Credentials do not match
}

void handle_login(const char *username, const char *password) {
    if (username == NULL || password == NULL) {
        printf("HTTP/1.1 500 Internal Server Error\n");
        printf(INTERNAL_SERVER_ERROR);
        return;
    }

    if (check_credentials(username, password)) {
        printf("HTTP/1.1 302 Found\n");
        printf(SUCCESS);
    } else {
        printf("HTTP/1.1 302 Found\n");
        printf(CANT_LOGIN);
    }
}

int main() {
    char username[100], password[100];

    // Simulate form data
    strcpy(username, "user1"); // Change to simulate different inputs
    strcpy(password, "pass1"); // Change to simulate different inputs

    handle_login(username, password);

    return 0;
}