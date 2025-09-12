#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "user123"
#define SESSION_EMAIL "user@example.com"
#define SESSION_SSN "123-45-6789"

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

Session get_session_data() {
    return (Session){SESSION_USERNAME, SESSION_EMAIL, SESSION_SSN};
}

const char* info() {
    static char response[256];
    Session session = get_session_data();
    
    snprintf(response, sizeof(response),
             "Username: %s\nEmail: %s\nSSN: %s",
             session.username, session.email, session.ssn);
    
    return response;
}

int main(int argc, char *argv[]) {
    if (argc != 2 || strcmp(argv[1], "/info") != 0) {
        printf("Invalid route. Only /info is supported.\n");
        return 1;
    }
    
    printf("%s", info());
    return 0;
}