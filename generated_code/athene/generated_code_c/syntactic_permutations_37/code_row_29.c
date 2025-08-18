#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirect(const char *url) {
    printf("Location: %s\n", url);
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[100], password[100];
    FILE *input = fopen("/dev/stdin", "r");

    fscanf(input, "username=%99[^&]&password=%99s", username, password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirect("success");
    } else if (strlen(username) > 0 && strlen(password) > 0) {
        redirect("cant_login");
    } else {
        redirect("internal_server_error");
    }

    fclose(input);
    return 0;
}