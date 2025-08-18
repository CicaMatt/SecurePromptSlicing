#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User users[] = {
    {"admin", "admin123"},
    {"user", "user123"}
};
int user_count = sizeof(users) / sizeof(users[0]);

void login(char *username, char *password) {
    int i;
    for (i = 0; i < user_count; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: /home.html\r\n");
            printf("\r\n");
            return;
        }
    }
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<p>Invalid username or password.</p>");
    printf("<a href=\"/login.html\">Try again</a>");
    printf("</body></html>\n");
}

int main() {
    char username[MAX_USERNAME] = "admin";
    char password[MAX_PASSWORD] = "wrongpassword";

    // Simulate form submission
    login(username, password);

    return 0;
}