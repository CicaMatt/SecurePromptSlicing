#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    char *email;
    char *ssn;
} User;

const User user = {"john_doe", "john.doe@example.com", "123-45-6789"};

char* info() {
    static char response[200];
    snprintf(response, sizeof(response), "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}", user.username, user.email, user.ssn);
    return response;
}

int main() {
    printf("Content-Type: application/json\n\n");
    printf("%s", info());
    return 0;
}