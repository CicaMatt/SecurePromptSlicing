#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void info(Session *session) {
    printf("HTTP/1.1 200 OK\nContent-Type: text/plain\n\n");
    printf("Username: %s\n", session->username);
    printf("Email: %s\n", session->email);
    printf("SSN: %s\n", session->ssn);
}

int main() {
    Session session = {
        .username = "user123",
        .email = "user@example.com",
        .ssn = "123-45-6789"
    };

    char route[10];
    scanf("%s", route);

    if (strcmp(route, "/info") == 0) {
        info(&session);
    } else {
        printf("HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\n");
        printf("Route not found.\n");
    }

    return 0;
}