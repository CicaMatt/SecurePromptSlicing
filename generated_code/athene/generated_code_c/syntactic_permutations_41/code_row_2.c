#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn_last_4;
} UserInfo;

void handle_info_request(UserInfo user) {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", user.username);
    printf("<p>Email: %s</p>", user.email);
    printf("<p>Last 4 digits of SSN: %s</p>", user.ssn_last_4);
    printf("</body></html>");
}

int main() {
    UserInfo user = {
        .username = "john_doe",
        .email = "john.doe@example.com",
        .ssn_last_4 = "1234"
    };

    // Simulate handling of /info route
    handle_info_request(user);

    return 0;
}