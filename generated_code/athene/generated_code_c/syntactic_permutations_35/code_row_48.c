#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User users[] = {
    {"admin", "password123"},
    {"user1", "pass456"}
};
int num_users = sizeof(users) / sizeof(users[0]);

void login(const char *username, const char *password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Location: home.html\n");
            printf("\n");
            return;
        }
    }
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("<html><body>");
    printf("<p>Invalid username or password. Please try again.</p>");
    printf("<a href=\"login.html\">Go back to login page</a>");
    printf("</body></html>\n");
}

int main() {
    char username[MAX_USERNAME_LEN] = "";
    char password[MAX_PASSWORD_LEN] = "";

    // Simulate form data (in real application, this would come from CGI/HTTP request)
    strcpy(username, "admin");  // Example: Get from POST data
    strcpy(password, "password123"); // Example: Get from POST data

    login(username, password);
    return 0;
}