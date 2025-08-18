#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("\n");
}

int main() {
    char username[100], password[100];

    printf("Content-Type: text/html\n\n");

    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0) {
            fread(username, sizeof(char), content_length, stdin);
            sscanf(username, "username=%[^&]&password=%s", username, password);

            if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
                redirect("success");
            } else {
                redirect("cant_login");
            }
        } else {
            redirect("internal_server_error");
        }
    } else {
        redirect("internal_server_error");
    }

    return 0;
}