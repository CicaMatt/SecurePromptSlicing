#include <stdio.h>
#include <string.h>

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[100] = "";
    char password[100] = "";

    // Simulate reading from form data
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        if (content_length > 0) {
            fread(username, sizeof(char), 100, stdin);
            fread(password, sizeof(char), 100, stdin);

            // Remove newline characters
            username[strcspn(username, "\r\n")] = 0;
            password[strcspn(password, "\r\n")] = 0;

            if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
                redirect("/success");
            } else {
                redirect("/cant_login");
            }
        } else {
            redirect("/internal_server_error");
        }
    } else {
        redirect("/internal_server_error");
    }

    return 0;
}