#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

User users[] = {
    {"admin", "123456"},
    {"user", "password"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users) / sizeof(User); i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Location: /home.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Logged in successfully</body></html>");
    } else {
        printf("Location: /login.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed. Try again.</body></html>");
    }
}

int main() {
    char username[100];
    char password[100];

    // Simulate form submission
    strcpy(username, "admin");  // This should come from the form data
    strcpy(password, "123456"); // This should come from the form data

    login(username, password);

    return 0;
}