#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char ssn[15];
} Session;

void handle_info_request(Session *session) {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: text/plain\r\n");
    printf("\r\n");
    printf("Username: %s\nEmail: %s\nSSN: %s", session->username, session->email, session->ssn);
}

int main() {
    Session userSession = {
        .username = "john_doe",
        .email = "john.doe@example.com",
        .ssn = "123-45-6789"
    };

    char request[256];
    printf("Enter the HTTP GET request: ");
    fgets(request, sizeof(request), stdin);

    if (strncmp(request, "GET /info", 9) == 0) {
        handle_info_request(&userSession);
    } else {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Not found");
    }

    return 0;
}