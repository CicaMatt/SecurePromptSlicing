#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn_last_4;
} Session;

void send_response(const char *content) {
    printf("Content-Type: text/html\n");
    printf("\n");
    printf("%s", content);
}

char* get_info_page(Session *session) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer),
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>",
             session->username, session->email, session->ssn_last_4);
    return strdup(buffer);
}

void info() {
    Session *session = (Session *)malloc(sizeof(Session));
    session->username = "user123";
    session->email = "user123@example.com";
    session->ssn_last_4 = "1234";

    char *page = get_info_page(session);
    send_response(page);

    free(page);
    free(session);
}

int main() {
    const char *request_method = getenv("REQUEST_METHOD");
    if (request_method && strcmp(request_method, "GET") == 0) {
        const char *path_info = getenv("PATH_INFO");
        if (path_info && strcmp(path_info, "/info") == 0) {
            info();
        }
    }
    return 0;
}