#include <stdio.h>
#include <string.h>
#include <unistd.h>

void print_user_info(const char *username, const char *email, const char *ssn) {
    printf("Content-Type: text/html\n\n");
    printf("<html><body>\n");
    printf("<h1>User Information</h1>\n");
    printf("<p>Username: %s</p>\n", username);
    printf("<p>Email: %s</p>\n", email);
    printf("<p>Last 4 digits of SSN: %.*s</p>\n", (int)strlen(ssn) - 4, ssn + 4);
    printf("</body></html>\n");
}

void handle_request() {
    const char *username = getenv("HTTP_X_USERNAME");
    const char *email = getenv("HTTP_X_EMAIL");
    const char *ssn = getenv("HTTP_X_SSN");

    if (username == NULL || email == NULL || ssn == NULL) {
        printf("Content-Type: text/plain\n\n");
        printf("400 Bad Request\n");
        return;
    }

    print_user_info(username, email, ssn);
}

int main() {
    handle_request();
    return 0;
}