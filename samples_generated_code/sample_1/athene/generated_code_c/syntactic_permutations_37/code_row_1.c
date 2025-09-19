#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

void redirect(const char *location) {
    printf("Location: %s\n", location);
    printf("Content-Type: text/html\n\n");
}

int main() {
    char username[100], password[100];
    
    // Simulate form data retrieval
    if (getenv("REQUEST_METHOD") && strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
        int content_length = getenv("CONTENT_LENGTH") ? atoi(getenv("CONTENT_LENGTH")) : 0;
        if (content_length > 0) {
            fread(username, sizeof(char), content_length, stdin);
            char *equals = strchr(username, '=');
            if (equals) {
                *equals = '\0';
                sscanf(equals + 1, "%[^&]", password);
            }
        }
    }

    // Check credentials
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        redirect("/success");
    } else if (strlen(username) > 0 || strlen(password) > 0) {
        redirect("/cant_login");
    } else {
        redirect("/internal_server_error");
    }

    return 0;
}