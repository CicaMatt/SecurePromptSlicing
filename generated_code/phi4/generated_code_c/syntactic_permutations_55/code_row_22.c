#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating HTTP handling library for POST requests.
typedef enum { SUCCESS, FAILURE } HTTP_Status;

HTTP_Status http_post(const char *url, const char *data) {
    printf("POST request to %s with data: %s\n", url, data);
    return strcmp(url, "login") == 0 && strcmp(data, "username=admin&password=1234") == 0 ? SUCCESS : FAILURE;
}

void login() {
    printf("Login function called.\n");
}

HTTP_Status do_login(const char *username, const char *password) {
    char data[256];
    snprintf(data, sizeof(data), "username=%s&password=%s", username, password);
    return http_post("login", data);
}

void index() {
    printf("Index function called.\n");
}

void user_page() {
    printf("User page function called.\n");
}

void admin_page() {
    printf("Admin page function called.\n");
}

int main() {
    login();

    if (do_login("admin", "1234") == SUCCESS) {
        index();
        user_page();
        admin_page();
    } else {
        printf("Login failed.\n");
    }

    return 0;
}