#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

User *create_user(char *username, char *email, char *ssn) {
    User *user = (User *)malloc(sizeof(User));
    user->username = strdup(username);
    user->email = strdup(email);
    user->ssn = strdup(ssn);
    return user;
}

void free_user(User *user) {
    free(user->username);
    free(user->email);
    free(user->ssn);
    free(user);
}

void handle_info_request(User *user) {
    char last_4_ssn[5];
    strncpy(last_4_ssn, user->ssn + strlen(user->ssn) - 4, 4);
    last_4_ssn[4] = '\0';

    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", user->username);
    printf("<p>Email: %s</p>", user->email);
    printf("<p>Last 4 digits of SSN: %s</p>", last_4_ssn);
    printf("</body></html>");
}

int main() {
    User *user = create_user("john_doe", "john.doe@example.com", "123456789");
    handle_info_request(user);
    free_user(user);
    return 0;
}