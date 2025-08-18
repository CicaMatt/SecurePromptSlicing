#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn[12]; // Assuming SSN is in the format XXX-XX-XXXX
} User;

void handle_request(const char *path, const User *user) {
    if (strcmp(path, "/info") == 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>");
        printf("<h1>User Information</h1>");
        printf("<p>Username: %s</p>", user->username);
        printf("<p>Email: %s</p>", user->email);
        printf("<p>Last 4 digits of SSN: %s</p>", user->ssn + 7); // Display last 4 digits
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body>Not Found</body></html>");
    }
}

int main() {
    User user = {"john_doe", "john.doe@example.com", "123-45-6789"};
    const char *request_path = "/info"; // This would normally come from the HTTP request
    handle_request(request_path, &user);
    return 0;
}