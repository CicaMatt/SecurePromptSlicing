#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

User users[] = {
    {"admin", "admin123"},
    {"user", "pass123"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users)/sizeof(users[0]); i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *location) {
    printf("Location: %s\r\n", location);
    printf("Content-Type: text/html\r\n\r\n");
}

int main() {
    char username[100], password[100];
    
    // Simulate form submission
    strcpy(username, getenv("username"));
    strcpy(password, getenv("password"));

    if (strlen(username) == 0 || strlen(password) == 0) {
        redirect("/internal_server_error");
        return 1;
    }

    if (authenticate(username, password)) {
        redirect("/success");
    } else {
        redirect("/login?error=1");
    }
    
    return 0;
}