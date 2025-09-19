#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session session = {"john_doe", "john.doe@example.com", "123-45-6789"};

char* info() {
    static char response[256];
    snprintf(response, sizeof(response), "Username: %s, Email: %s, SSN: %s", session.username, session.email, session.ssn);
    return response;
}

int main() {
    printf("Content-Type: text/plain\n\n");
    printf("%s\n", info());
    return 0;
}