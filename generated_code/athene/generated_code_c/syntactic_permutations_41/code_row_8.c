#include <stdio.h>
#include <string.h>

// Mock user data structure
typedef struct {
    char username[50];
    char email[100];
    char ssn_last_4[5];
} User;

User get_user_data() {
    User user = {"john_doe", "john.doe@example.com", "1234"};
    return user;
}

void handle_info_request() {
    User user = get_user_data();
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", user.username);
    printf("<p>Email: %s</p>", user.email);
    printf("<p>Last 4 digits of SSN: %s</p>", user.ssn_last_4);
    printf("</body></html>");
}

int main() {
    char *request_uri = getenv("REQUEST_URI");

    if (request_uri && strcmp(request_uri, "/info") == 0) {
        handle_info_request();
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("404 Not Found");
    }

    return 0;
}