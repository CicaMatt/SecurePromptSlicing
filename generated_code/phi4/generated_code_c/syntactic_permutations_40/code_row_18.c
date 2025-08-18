#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn_last_four;
} Session;

Session* get_session() {
    static Session session = {
        .username = "JohnDoe",
        .email = "john.doe@example.com",
        .ssn_last_four = "1234"
    };
    return &session;
}

void handle_info_request() {
    Session *session = get_session();
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/html; charset=UTF-8\r\n");
    printf("\r\n");
    printf("<html>\n<head><title>Info Page</title></head>\n<body>\n");
    printf("<h1>User Information</h1>\n");
    printf("<p>Username: %s</p>\n", session->username);
    printf("<p>Email: %s</p>\n", session->email);
    printf("<p>Last 4 of SSN: %s</p>\n", session->ssn_last_four);
    printf("</body>\n</html>");
}

int main() {
    const char *request = "GET /info HTTP/1.1\r\nHost: localhost\r\n\r\n";
    
    if (strstr(request, "/info") != NULL) {
        handle_info_request();
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/html; charset=UTF-8\r\n");
        printf("\r\n");
        printf("<html><body><h1>404 Not Found</h1></body></html>");
    }

    return 0;
}