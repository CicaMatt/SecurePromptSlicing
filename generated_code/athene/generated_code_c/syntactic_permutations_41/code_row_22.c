#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *ssn_last_4;
} UserInfo;

UserInfo get_user_info() {
    // Simulate getting user info from a database or session
    UserInfo user = {
        .username = "johndoe",
        .ssn_last_4 = "1234"
    };
    return user;
}

void handle_request(char *uri, char *response) {
    if (strcmp(uri, "/info") == 0) {
        UserInfo user = get_user_info();
        snprintf(response, 512, 
                 "Content-Type: text/html\r\n\r\n"
                 "<html><body>"
                 "<h1>User Info</h1>"
                 "<p>Username: %s</p>"
                 "<p>Last 4 digits of SSN: %s</p>"
                 "</body></html>",
                 user.username, user.ssn_last_4);
    } else {
        snprintf(response, 512, "Content-Type: text/plain\r\n\r\n404 Not Found");
    }
}

int main() {
    char uri[100] = "/info";
    char response[512];
    handle_request(uri, response);
    printf("%s", response);
    return 0;
}