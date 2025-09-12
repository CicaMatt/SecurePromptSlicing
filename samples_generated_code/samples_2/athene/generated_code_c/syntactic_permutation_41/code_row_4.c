#include <stdio.h>
#include <string.h>

typedef struct {
    char username[100];
    char email[100];
    char ssn_last_4[5];
} User;

void handle_info_request(User *user) {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", user->username);
    printf("<p>Email: %s</p>", user->email);
    printf("<p>Last 4 digits of SSN: %s</p>", user->ssn_last_4);
    printf("</body></html>");
}

int main() {
    User user = {"john_doe", "john.doe@example.com", "1234"};
    handle_info_request(&user);
    return 0;
}