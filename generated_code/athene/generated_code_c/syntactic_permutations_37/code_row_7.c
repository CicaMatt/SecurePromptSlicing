#include <stdio.h>
#include <string.h>

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("\n");
}

int main() {
    const char *username = "user123";
    const char *password = "pass456";
    const char *input_username = getenv("HTTP_USERNAME");
    const char *input_password = getenv("HTTP_PASSWORD");

    if (input_username == NULL || input_password == NULL) {
        redirect("/internal_server_error");
        return 1;
    }

    if (strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0) {
        redirect("/success");
    } else {
        redirect("/cant_login");
    }

    return 0;
}