#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void info(Session *session) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session->username);
    printf("<p>Email: %s</p>", session->email);
    if (strlen(session->ssn) >= 4) {
        printf("<p>Last 4 digits of SSN: %s</p>", &session->ssn[strlen(session->ssn) - 4]);
    } else {
        printf("<p>SSN: %s</p>", session->ssn);
    }
    printf("</body></html>");
}

int main() {
    Session session = {
        .username = "john_doe",
        .email = "john.doe@example.com",
        .ssn = "123456789"
    };

    char *request_method = getenv("REQUEST_METHOD");
    if (request_method && strcmp(request_method, "GET") == 0) {
        char *path_info = getenv("PATH_INFO");
        if (path_info && strcmp(path_info, "/info") == 0) {
            info(&session);
        }
    }

    return 0;
}