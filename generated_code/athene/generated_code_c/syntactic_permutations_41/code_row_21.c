#include <stdio.h>
#include <string.h>

void send_response(const char *username, const char *email, const char *ssn) {
    printf("Content-Type: text/html\r\n\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", username);
    printf("<p>Email: %s</p>", email);
    printf("<p>Last 4 digits of SSN: %s</p>", ssn + strlen(ssn) - 4);
    printf("</body></html>");
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (request_method && strcmp(request_method, "GET") == 0) {
        char *path_info = getenv("PATH_INFO");
        if (path_info && strcmp(path_info, "/info") == 0) {
            const char *username = "user123";
            const char *email = "user123@example.com";
            const char *ssn = "123456789";
            send_response(username, email, ssn);
        } else {
            printf("Content-Type: text/html\r\n\r\n");
            printf("<html><body><h1>404 Not Found</h1></body></html>");
        }
    } else {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><body><h1>Method Not Allowed</h1></body></html>");
    }
    return 0;
}