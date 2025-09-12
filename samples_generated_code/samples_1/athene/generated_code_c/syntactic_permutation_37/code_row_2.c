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
    
    // Simulate receiving data from a form
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        fread(username, sizeof(char), 99, stdin);
        username[99] = '\0';
        fread(password, sizeof(char), 99, stdin);
        password[99] = '\0';

        // Remove trailing newline characters
        username[strcspn(username, "\r\n")] = 0;
        password[strcspn(password, "\r\n")] = 0;

        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            redirect("success.html");
        } else {
            redirect("login_error.html");
        }
    } else {
        redirect("internal_server_error.html");
    }

    return 0;
}