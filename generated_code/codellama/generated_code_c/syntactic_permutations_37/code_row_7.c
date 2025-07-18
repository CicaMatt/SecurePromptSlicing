#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../lib/http.h"

int main(void) {
    // 1. Get the username and password from the client's HTTP request body.
    const char* username = getenv("HTTP_USERNAME");
    const char* password = getenv("HTTP_PASSWORD");
    
    // 2. Validate that both a username and password were provided.
    if (username == NULL || password == NULL) {
        printf("Status: 500 Internal Server Error\r\n\r\n");
        return 1;
    }

    // 3. Check the username and password against a list of valid credentials.
    int is_valid_credential = 0;

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        is_valid_credential = 1;
    }

    // 4. Redirect the client to a different page based on the result of the credentials check.
    if (is_valid_credential) {
        printf("Status: 302 Found\r\n");
        printf("Location: https://example.com/success\r\n\r\n");
    } else {
        printf("Status: 302 Found\r\n");
        printf("Location: https://example.com/cant_login\r\n\r\n");
    }

    return 0;
}