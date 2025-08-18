#include <stdio.h>
#include <string.h>

typedef struct {
    char username[100];
    char password[100];
} User;

User users[] = {
    {"admin", "password123"},
    {"user1", "pass456"}
};

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users)/sizeof(User); i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password) {
    if (authenticate(username, password)) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>");
        printf("<h1>Login Successful</h1>");
        printf("</body></html>");
    } else {
        printf("Location: login.html\n\n");
    }
}

int main() {
    char username[100];
    char password[100];

    // Simulate form data (in a real CGI script, this would come from the environment)
    const char *form_data = "username=admin&password=password123";
    sscanf(form_data, "username=%[^&]&password=%s", username, password);

    login(username, password);
    return 0;
}