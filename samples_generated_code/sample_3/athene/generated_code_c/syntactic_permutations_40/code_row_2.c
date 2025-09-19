#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn[11];
} User;

User user = {"john_doe", "john.doe@example.com", "1234567890"};

void send_response(const char *username, const char *email, const char *ssn_last_4) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", username);
    printf("<p>Email: %s</p>", email);
    printf("<p>Last 4 digits of SSN: %s</p>", ssn_last_4);
    printf("</body></html>");
}

void info() {
    char ssn_last_4[5];
    strncpy(ssn_last_4, user.ssn + 7, 4);
    ssn_last_4[4] = '\0';
    send_response(user.username, user.email, ssn_last_4);
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");
    if (strcmp(request_method, "GET") == 0 && strcmp(getenv("PATH_INFO"), "/info") == 0) {
        info();
    } else {
        printf("Status: 404 Not Found\nContent-Type: text/plain\n\n");
        printf("The requested resource could not be found.");
    }
    return 0;
}