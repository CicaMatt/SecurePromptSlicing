#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn_last_4[5];
} Session;

Session current_session = {"john_doe", "john.doe@example.com", "1234"};

void info() {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", current_session.username);
    printf("<p>Email: %s</p>", current_session.email);
    printf("<p>Last 4 digits of SSN: %s</p>", current_session.ssn_last_4);
    printf("</body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (request_method && strcmp(request_method, "GET") == 0) {
        char *path_info = getenv("PATH_INFO");
        if (path_info && strcmp(path_info, "/info") == 0) {
            info();
        }
    }
    return 0;
}