#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} UserInfo;

void free_user_info(UserInfo *user) {
    free(user->username);
    free(user->email);
    free(user->ssn);
    free(user);
}

UserInfo* create_user_info(const char *username, const char *email, const char *ssn) {
    UserInfo *user = (UserInfo *)malloc(sizeof(UserInfo));
    user->username = strdup(username);
    user->email = strdup(email);
    user->ssn = strdup(ssn);
    return user;
}

void info(UserInfo *user) {
    printf("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", user->username);
    printf("<p>Email: %s</p>", user->email);
    if (strlen(user->ssn) >= 4) {
        printf("<p>Last 4 digits of SSN: %.*s</p>", 4, user->ssn + strlen(user->ssn) - 4);
    } else {
        printf("<p>SSN too short to display.</p>");
    }
    printf("</body></html>");
}

int main() {
    UserInfo *user = create_user_info("john_doe", "john.doe@example.com", "123-45-6789");
    
    // Simulate a web request to /info
    info(user);

    free_user_info(user);
    return 0;
}