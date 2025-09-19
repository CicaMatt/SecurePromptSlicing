#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

typedef struct {
    char *username;
    char *email;
    char *ssn;
} UserInfo;

UserInfo *create_user_info(const char *username, const char *email, const char *ssn) {
    UserInfo *info = (UserInfo *)malloc(sizeof(UserInfo));
    info->username = strdup(username);
    info->email = strdup(email);
    info->ssn = strdup(ssn + strlen(ssn) - 4); // Last 4 digits of SSN
    return info;
}

void free_user_info(UserInfo *info) {
    if (info) {
        free(info->username);
        free(info->email);
        free(info->ssn);
        free(info);
    }
}

void handle_request(char *request, UserInfo *user) {
    char response[1024];
    snprintf(response, sizeof(response),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/html\r\n"
             "\r\n"
             "<html><body>"
             "<h1>User Information</h1>"
             "<p>Username: %s</p>"
             "<p>Email: %s</p>"
             "<p>Last 4 digits of SSN: %s</p>"
             "</body></html>", user->username, user->email, user->ssn);
    printf("%s", response);
}

int main() {
    char request[MAX_REQUEST_SIZE];
    UserInfo *user = create_user_info("john_doe", "john.doe@example.com", "123-45-6789");

    while (1) {
        fgets(request, sizeof(request), stdin);
        if (strstr(request, "/info") != NULL) {
            handle_request(request, user);
        } else {
            printf("HTTP/1.1 404 Not Found\r\n"
                   "Content-Type: text/html\r\n"
                   "\r\n"
                   "<html><body>404 - Page not found</body></html>\n");
        }
    }

    free_user_info(user);
    return 0;
}